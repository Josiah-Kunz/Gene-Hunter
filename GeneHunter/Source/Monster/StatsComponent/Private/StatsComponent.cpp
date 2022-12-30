#include "StatsComponent.h"

#include "EffectUtilities.h"
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
		/*
		if (LevelComponent == nullptr)
			LevelComponent = Owner->FindComponentByClass<ULevelComponent>();
		if (LevelComponent == nullptr)
		{
			LevelComponent = NewObject<ULevelComponent>(Owner, TEXT("Level Component"));
			Owner->AddInstanceComponent(LevelComponent);
			LevelComponent->RegisterComponent();
		}*/

		// Anything changed?
		if (LevelComponent != nullptr && LevelComponent != OldLevelComponent)
		{
			// Delegate for changing stats on level up
			ULevelComponent::FSetCumulativeExpDelegate UpdateStatsAfterLevelUp;
			UpdateStatsAfterLevelUp.BindLambda([this](const int OldCXP, const int NewCXP)
			{
				const int OldLevel = ULevelComponent::GetLevelFromCXP(OldCXP);
				const int NewLevel = ULevelComponent::GetLevelFromCXP(NewCXP);
				if (NewLevel != OldLevel)
					RecalculateStats();
			});
			LevelComponent->AfterSetCumulativeExpArray.Add(UpdateStatsAfterLevelUp);
	
			// Start with random stats
			RandomizeStats();
		}
	}
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	


	/*
	ULevelComponent::FSetLevelDelegate UpdateStatsAfterLevelUp;
	UpdateStatsAfterLevelUp.BindLambda([this](const int ){
		for(FStat* Stat : StatsArray)
			Stat->Update(LevelComponent->GetLevel());
	});
	LevelComponent->AfterSetLevelArray.Add(UpdateStatsAfterLevelUp);
	*/
	
}

void UStatsComponent::RandomizeStats(
	int MinBaseStat, int MaxBaseStat,
	int MinBasePairs, int MaxBasePairs)
{

	ExecuteBeforeRandomizeStats(MinBaseStat, MaxBaseStat, MinBasePairs, MaxBasePairs);
	
	for(FStat* Stat : StatsArray)
	{
		if (MaxBaseStat > MinBaseStat)
			Stat->BaseStat = FMath::RandRange(MinBaseStat, MaxBaseStat);
		if (MaxBasePairs > MinBasePairs)
			Stat->BasePairs = FMath::RandRange(MinBasePairs, MaxBasePairs);
		Stat->Update(LevelComponent->GetLevel());
	}

	ExecuteAfterRandomizeStats(MinBaseStat, MaxBaseStat, MinBasePairs, MaxBasePairs);
}

void UStatsComponent::RandomizeBasePairs(const int MinBasePairs, const int MaxBasePairs)
{
	RandomizeStats(0, -1, MinBasePairs, MaxBasePairs);
}

void UStatsComponent::RandomizeBaseStats(const int MinBaseStats, const int MaxBaseStats)
{
	RandomizeStats(MinBaseStats, MaxBaseStats, 0, -1);
}


void UStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		ModifyStatInternal(StatsArray[i], Values[i], ValueType, Mode);
}

void UStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(FStat* Stat : StatsArray)
		ModifyStatInternal(Stat, UniformMod, ValueType, Mode);
}

void UStatsComponent::RecalculateStats(const bool bResetCurrent)
{
	for(FStat* Stat : StatsArray)
	{
		ExecuteBeforeRecalculateStats(Stat, bResetCurrent);
		Stat->Update(LevelComponent->GetLevel(), bResetCurrent);
		ExecuteAfterRecalculateStats(Stat, bResetCurrent);
	}
}

void UStatsComponent::ModifyStatInternal(FStat* Stat, float Value, EStatValueType ValueType, EModificationMode Mode)
{
	ExecuteBeforeModifyStat(Stat, Value, ValueType, Mode);
	Stat->ModifyValue(Value, ValueType, Mode);
	ExecuteAfterModifyStat(Stat, Value, ValueType, Mode);
}

bool UStatsComponent::IsEqual(UStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
{
	
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(StatsArray[i]->GetCurrentValue() - Other->StatsArray[i]->GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(StatsArray[i]->GetPermanentValue() - Other->StatsArray[i]->GetPermanentValue() > Tolerance))
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
	for(const FStat* Stat : StatsArray)
		Ret += Stat->BaseStat;
	return Ret;
}

float UStatsComponent::BaseStatEffectiveAverage()
{

	// Get base stat total
	float BST = BaseStatTotal();
	
	// Number to divide by
	int Denominator = StatsArray.Num();

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
