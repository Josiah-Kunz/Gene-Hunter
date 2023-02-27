#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"
#include "MathUtil.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UCombatStatsComponent::UCombatStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatStatsComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	EnsureLevelComponent(GetOwner());
}

void UCombatStatsComponent::EnsureLevelComponent(AActor* Owner)
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
			UpdateStatsAfterLevel.Delegate.BindDynamic(this, &UCombatStatsComponent::ChangeStatsOnLevelChange);
			LevelComponent->SetCXPOutlet.AddAfter(UpdateStatsAfterLevel);
			
			// Start with random stats
			RandomizeStatsCustom(FStatRandParams{});
		}
	}
}

void UCombatStatsComponent::ChangeStatsOnLevelChange(const uint32 OldCXP, const int32 InputCXP, const int32 AttemptedCXP)
{
	const uint32 OldLevel = ULevelComponent::GetLevelFromCXP(OldCXP);
	const uint32 NewLevel = ULevelComponent::GetLevelFromCXP(AttemptedCXP);
	if (NewLevel != OldLevel)
	{
		RecalculateStats(true);
	}
}

// Called when the game starts
void UCombatStatsComponent::BeginPlay()
{
	Super::BeginPlay();
}

const FCombatStat& UCombatStatsComponent::GetStat(const EStatEnum Stat)
{
	return GetStatMutable(Stat);
}

FCombatStat& UCombatStatsComponent::GetStatMutable(const EStatEnum Stat)
{
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
		UE_LOG(LogTemp, Error, TEXT("%s::GetStat(EStatEnum::%s) not coded! Please update the source files."),
			*UCombatStatsComponent::StaticClass()->GetName(),
			*(UEnum::GetValueAsString(Stat))
		)
		return Health;
	}
}

void UCombatStatsComponent::RandomizeStat_Internal(const EStatEnum Stat, const FStatRandParams OriginalParams, FStatRandParams Params)
{
	// Before delegates
	RandomizeStatsOutlet.ExecuteBefore(Stat, OriginalParams, Params);

	// Special, intentional cases: if max <= min, don't randomize it
	if (Params.MaxBaseStat > Params.MinBaseStat)
	{
		ModifyStat(Stat,
			FMath::RandRange(Params.MinBaseStat, Params.MaxBaseStat),
			EStatValueType::BaseStat,
			EModificationMode::SetDirectly
		);
	}
	if (Params.MaxBasePairs > Params.MinBasePairs)
	{
		ModifyStat(Stat,
			FMath::RandRange(Params.MinBasePairs, Params.MaxBasePairs),
			EStatValueType::BasePairs,
			EModificationMode::SetDirectly
		);
	}

	// After delegate
	RandomizeStatsOutlet.ExecuteAfter(Stat, OriginalParams, Params);
}

void UCombatStatsComponent::RandomizeStat(const EStatEnum Stat, const FStatRandParams Params)
{
	// Cache original for delegates
	const FStatRandParams OriginalParams = Params;

	// Call internal
	RandomizeStat_Internal(Stat, Params, Params);
}

void UCombatStatsComponent::RandomizeBasePair(const EStatEnum Stat, const int32 MinBasePairs, const int32 MaxBasePairs)
{
	FStatRandParams Params;
	Params.MinBaseStat = 0;
	Params.MaxBaseStat = -1;
	Params.MinBasePairs = MinBasePairs;
	Params.MaxBasePairs = MaxBasePairs;
	RandomizeStat(Stat, Params);
}

void UCombatStatsComponent::RandomizeBaseStat(const EStatEnum Stat, const int32 MinBaseStats, const int32 MaxBaseStats)
{
	FStatRandParams Params;
	Params.MinBaseStat = MinBaseStats;
	Params.MaxBaseStat = MaxBaseStats;
	Params.MinBasePairs = 0;
	Params.MaxBasePairs = -1;
	RandomizeStat(Stat, Params);
}

void UCombatStatsComponent::RandomizeStats()
{
	FStatRandParams Params;
	Params.MinBasePairs = 1;
	Params.MaxBasePairs = 100;
	Params.MinBaseStat = 50;
	Params.MaxBaseStat = 150;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::RandomizeStatsCustom(const FStatRandParams Params)
{

	// Cache original for delegates
	const FStatRandParams OriginalParams = Params;
	
	for(const EStatEnum Stat : StatsArray)
	{
		RandomizeStat_Internal(Stat, OriginalParams, Params);
	}
}

void UCombatStatsComponent::RandomizeBasePairs(const int32 MinBasePairs, const int32 MaxBasePairs)
{
	FStatRandParams Params;
	Params.MinBaseStat = 0;
	Params.MaxBaseStat = -1;
	Params.MinBasePairs = MinBasePairs;
	Params.MaxBasePairs = MaxBasePairs;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::RandomizeBaseStats(const int32 MinBaseStats, const int32 MaxBaseStats)
{
	FStatRandParams Params;
	Params.MinBaseStat = MinBaseStats;
	Params.MaxBaseStat = MaxBaseStats;
	Params.MinBasePairs = 0;
	Params.MaxBasePairs = -1;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::ModifyStat(const EStatEnum Stat, const float Value, const EStatValueType ValueType,
                                       const EModificationMode Mode)
{
	ModifyStatInternal(Stat, Value, ValueType, Mode);
}


void UCombatStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		ModifyStat(StatsArray[i], Values[i], ValueType, Mode);
}

void UCombatStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(const EStatEnum Stat : StatsArray)
		ModifyStat(Stat, UniformMod, ValueType, Mode);
}

void UCombatStatsComponent::RecalculateStats(const bool bResetCurrent)
{
	for(const EStatEnum Stat : StatsArray)
	{

		// Cache for delegates
		FCombatStat& TargetStat = GetStatMutable(Stat);
		const float OriginalCurrent = TargetStat.GetCurrentValue();
		const float OriginalPermanent = TargetStat.GetPermanentValue();

		// Call + execute + call
		RecalculateStatsOutlet.ExecuteBefore(Stat, bResetCurrent, OriginalCurrent, OriginalPermanent);
		TargetStat.Update(LevelComponent->GetLevel(), bResetCurrent);
		RecalculateStatsOutlet.ExecuteBefore(Stat, bResetCurrent, OriginalCurrent, OriginalPermanent);
	}
}

auto UCombatStatsComponent::ModifyStatInternal(const EStatEnum Stat, const float Value,
	const EStatValueType ValueType, const EModificationMode Mode) -> void
{

	// Cache for outlets
	const float OriginalValue = GetStat(Stat).GetValue(ValueType);
	float AttemptedValue = Value;

	// Before outlet
	ModifyStatOutlet.ExecuteBefore(
				Stat,
				ValueType,
				Mode,
				OriginalValue,
				AttemptedValue
			);
	
	// Get stat and modify it
	FCombatStat& TargetStat = GetStatMutable(Stat);
	TargetStat.ModifyValue(AttemptedValue, ValueType, Mode);
	
	// After outlet
	ModifyStatOutlet.ExecuteAfter(
				Stat,
				ValueType,
				Mode,
				OriginalValue,
				AttemptedValue
			);
}

bool UCombatStatsComponent::IsEqual(UCombatStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
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
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UCombatStatsComponent::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}

float UCombatStatsComponent::BaseStatTotal()
{
	float Ret = 0;
	for(const EStatEnum Stat : StatsArray)
		Ret += GetStat(Stat).BaseStat;
	return Ret;
}

float UCombatStatsComponent::BaseStatEffectiveAverage()
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

float UCombatStatsComponent::GetModifiedValue(const EStatEnum Stat, const float ModValue, const EStatValueType ValueType,
	const EModificationMode Mode)
{

	const float CurrentValue = GetStat(Stat).GetValue(ValueType);
	return GetStat(Stat).GetModification(CurrentValue, Mode, ModValue);
}

void UCombatStatsComponent::AvertReduction(const EStatEnum Stat, float& Value, const EStatValueType ValueType,
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
		const FCombatStat& TargetStat = GetStat(Stat);
		if (Value < TargetStat.GetValue(ValueType))
			Value = TargetStat.GetValue(ValueType);
	}

	UE_LOG(LogTemp, Error, TEXT("AvertReduction cannot handle specified Mode [%s]!"), *UEnum::GetValueAsString(Mode))
}
