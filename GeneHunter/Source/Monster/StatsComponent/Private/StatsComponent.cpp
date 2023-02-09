#include "StatsComponent.h"

#include "ComponentUtilities.h"
#include "MathUtil.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UStatsComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	EnsureLevelComponent(GetOwner());
}

void UStatsComponent::EnsureLevelComponent(AActor* Owner)
{
	if (Owner != nullptr)
	{

		// Cache
		const ULevelComponent* OldLevelComponent = LevelComponent;

		// Find or create
		REQUIRE_COMPONENT(ULevelComponent, LevelComponent, Owner)

		// Anything changed?
		if (LevelComponent != nullptr && LevelComponent != OldLevelComponent)
		{

			// Delegate to ensure refreshing stats upon level change
			UpdateStatsAfterLevel.Delegate.Clear();
			UpdateStatsAfterLevel.Priority = IntrinsicPriority;
			UpdateStatsAfterLevel.Delegate.BindDynamic(this, &UStatsComponent::ChangeStatsOnLevelChange);
			LevelComponent->SetCXPOutlet.AddAfter(UpdateStatsAfterLevel);
			
			// Start with random stats
			RandomizeStats();
		}
	}
}

void UStatsComponent::ChangeStatsOnLevelChange(const uint32 OldCXP, const int32 AttemptedCXP)
{
	const uint32 OldLevel = ULevelComponent::GetLevelFromCXP(OldCXP);
	const uint32 NewLevel = ULevelComponent::GetLevelFromCXP(AttemptedCXP);
	if (NewLevel != OldLevel)
	{
		RecalculateStats(true);
	}
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

FStat& UStatsComponent::GetStat(const EStatEnum Stat){
	switch(Stat)
	{
	case EStatEnum::Health:
		return Health;
	case EStatEnum::PhysicalAttack:
		return PhysicalAttack;
	case EStatEnum::PhysicalDefense:
		return PhysicalDefense;
	case EStatEnum::SpecialAttack:
		return SpecialAttack;
	case EStatEnum::SpecialDefense:
		return SpecialDefense;
	case EStatEnum::Haste:
		return Haste;
	case EStatEnum::CriticalHit:
		return CriticalHit;
	default:
		UE_LOG(LogTemp, Error, TEXT("UStatsComponent::GetStat(EStatEnum::%s) not coded! Please update the source files."),
			*(UEnum::GetValueAsString(Stat))
		)
		return Health;
	}
}

void UStatsComponent::RandomizeStats(FStatRandParams Params)
{

	// Cache original for delegates
	const FStatRandParams OriginalParams = Params;
	
	for(const EStatEnum Stat : StatsArray)
	{

		// Before delegates
		RandomizeStatsOutlet.ExecuteBefore(Stat, OriginalParams, Params);

		// Special, intentional cases: if max <= min, don't randomize it
		if (Params.MaxBaseStat > Params.MinBaseStat)
			GetStat(Stat).BaseStat = FMath::RandRange(Params.MinBaseStat, Params.MaxBaseStat);
		if (Params.MaxBasePairs > Params.MinBasePairs)
			GetStat(Stat).BasePairs = FMath::RandRange(Params.MinBasePairs, Params.MaxBasePairs);

		// Update it
		GetStat(Stat).Update(LevelComponent->GetLevel());

		// After delegate
		RandomizeStatsOutlet.ExecuteAfter(Stat, OriginalParams, Params);
	}
}

void UStatsComponent::RandomizeBasePairs(const int32 MinBasePairs, const int32 MaxBasePairs)
{
	RandomizeStats(FStatRandParams{
		.MinBaseStat = 0,
		.MaxBaseStat = -1,
		.MinBasePairs = MinBasePairs,
		.MaxBasePairs = MaxBasePairs,
	});
}

void UStatsComponent::RandomizeBaseStats(const int32 MinBaseStats, const int32 MaxBaseStats)
{
	RandomizeStats({FStatRandParams{
		.MinBaseStat = MinBaseStats,
		.MaxBaseStat = MaxBaseStats,
		.MinBasePairs = 0,
		.MaxBasePairs = -1,
	}});
}

void UStatsComponent::ModifyStat(EStatEnum Stat, const float Value, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	ModifyStatInternal(Stat, Value, ValueType, Mode);
}


void UStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		ModifyStat(StatsArray[i], Values[i], ValueType, Mode);
}

void UStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(const EStatEnum Stat : StatsArray)
		ModifyStat(Stat, UniformMod, ValueType, Mode);
}

void UStatsComponent::RecalculateStats(const bool bResetCurrent)
{
	for(const EStatEnum Stat : StatsArray)
	{

		// Cache for delegates
		FStat& TargetStat = GetStat(Stat);
		const float OriginalCurrent = TargetStat.GetCurrentValue();
		const float OriginalPermanent = TargetStat.GetPermanentValue();

		// Call + execute + call
		RecalculateStatsOutlet.ExecuteBefore(Stat, bResetCurrent, OriginalCurrent, OriginalPermanent);
		TargetStat.Update(LevelComponent->GetLevel(), bResetCurrent);
		RecalculateStatsOutlet.ExecuteBefore(Stat, bResetCurrent, OriginalCurrent, OriginalPermanent);
	}
}

void UStatsComponent::ModifyStatInternal(EStatEnum Stat, float Value, EStatValueType ValueType, EModificationMode Mode)
{
	//ExecuteBeforeModifyStat(Stat, Value, ValueType, Mode);
	GetStat(Stat).ModifyValue(Value, ValueType, Mode);
	//ExecuteAfterModifyStat(Stat, Value, ValueType, Mode);
}

bool UStatsComponent::IsEqual(UStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
{
	
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(GetStat(StatsArray[i]).GetCurrentValue() - Other->GetStat(StatsArray[i]).GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(GetStat(StatsArray[i]).GetPermanentValue() - Other->GetStat(StatsArray[i]).GetPermanentValue() > Tolerance))
				return false;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UStatsComponent::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}

float UStatsComponent::BaseStatTotal()
{
	float Ret = 0;
	for(const EStatEnum Stat : StatsArray)
		Ret += GetStat(Stat).BaseStat;
	return Ret;
}

float UStatsComponent::BaseStatEffectiveAverage()
{

	// Get base stat total
	float BST = BaseStatTotal();
	
	// Number to divide by
	uint8 Denominator = StatsArray.Num();

	// Adjust: determine if we're using one or both
	const bool bUsePhA = PhysicalAttack.BaseStat > 0.9f * SpecialAttack.BaseStat;
	const bool bUseSpA = SpecialAttack.BaseStat > 0.9f * PhysicalAttack.BaseStat;
	if (!bUsePhA)
	{
		BST -= PhysicalAttack.BaseStat;
		Denominator--;
	}
	else if (!bUseSpA)
	{
		BST -= SpecialAttack.BaseStat;
		Denominator--;
	}

	// Return
	return BST/Denominator;
}

void UStatsComponent::AvertReduction(EStatEnum Stat, float& Value, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	switch(Mode)
	{
	case EModificationMode::AddAbsolute: case EModificationMode::AddFraction: case EModificationMode::AddPercentage:
		if (Value < 0)
			Value = 0;
		break;
	case EModificationMode::MultiplyAbsolute:
		if (Value < 1)
			Value = 1;
		break;
	case EModificationMode::MultiplyPercentage:
		if (Value < 100)
			Value = 100;
		break;
	case EModificationMode::SetDirectly:
		if (Value < GetStat(Stat).GetValue(ValueType))
			Value = GetStat(Stat).GetValue(ValueType);
	}

	UE_LOG(LogTemp, Error, TEXT("AvertReduction cannot handle specified Mode [%s]!"), *UEnum::GetValueAsString(Mode))
}
