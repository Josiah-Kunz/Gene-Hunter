#include "StatsBlock.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UStatsBlock::UStatsBlock()
{
	PrimaryComponentTick.bCanEverTick = false;
	RandomizeStats();
}

// Called when the game starts
void UStatsBlock::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsBlock::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

void UStatsBlock::RandomizeStats(
	const int MinBaseStat, const int MaxBaseStat,
	const int MinBasePairs, const int MaxBasePairs)
{
	TArray<UStat*> StatsArray;
	GetStatsArray(StatsArray);
	for(UStat* Stat : StatsArray)
	{
		if (MaxBaseStat > MinBaseStat)
			Stat->BaseStat = FMath::RandRange(MinBaseStat, MaxBaseStat);
		if (MaxBasePairs > MinBasePairs)
			Stat->BasePairs = FMath::RandRange(MinBasePairs, MaxBasePairs);
		Stat->Update(Level);
	}
}

void UStatsBlock::RandomizeBasePairs(const int MinBasePairs, const int MaxBasePairs)
{
	RandomizeStats(0, -1, MinBasePairs, MaxBasePairs);
}

void UStatsBlock::RandomizeBaseStats(const int MinBaseStats, const int MaxBaseStats)
{
	RandomizeStats(MinBaseStats, MaxBaseStats, 0, -1);
}



void UStatsBlock::ModifyStats(TMap<UStat*, int>& ValueMap, const EStatValueType ValueType, const EModificationMode Mode)
{

	// Affected stats
	TArray<UStat*> AffectedStats;
	ValueMap.GetKeys(AffectedStats);
	
	// Add stats
	for(int i=0; i<ValueMap.Num(); i++)
		AffectedStats[i]->ModifyValue(ValueMap[AffectedStats[i]], ValueType, Mode);
}

void UStatsBlock::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	TArray<UStat*> StatsArray;
	GetStatsArray(StatsArray);
	for(UStat* Stat : StatsArray)
		Stat->ModifyValue(UniformMod, ValueType, Mode);
}

void UStatsBlock::RandomizeStats_DetailsPanel()
{
	RandomizeStats( MinBaseStats_DetailsPanel, MaxBaseStats_DetailsPanel,
		MinBasePairs_DetailsPanel, MaxBasePairs_DetailsPanel);
}

void UStatsBlock::RandomizeBasePairs_DetailsPanel()
{
	RandomizeBasePairs(MinBasePairs_DetailsPanel, MaxBasePairs_DetailsPanel);
}

void UStatsBlock::RandomizeBaseStats_DetailsPanel()
{
	RandomizeBaseStats(MinBaseStats_DetailsPanel, MaxBaseStats_DetailsPanel);
}

bool UStatsBlock::IsEqual(UStatsBlock* Other, const EStatValueType ValueType, const float Tolerance)
{

	// StatValueType is redundant
	if (ValueType == EStatValueType::CurrentAndPermanent)
		return IsEqual(Other, EStatValueType::Current, Tolerance) && IsEqual(Other, EStatValueType::Permanent, Tolerance);
	
	TArray<UStat*> StatsArray, OtherStatsArray;
	GetStatsArray(StatsArray);
	Other->GetStatsArray(OtherStatsArray);
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(StatsArray[i]->GetCurrentValue() - OtherStatsArray[i]->GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(StatsArray[i]->GetPermanentValue() - OtherStatsArray[i]->GetPermanentValue() > Tolerance))
				return false;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UStatsBlock::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}


void UStatsBlock::GetStatsArray(TArray<UStat*>& Array)
{
	Array = {
		Health,
		PhysicalAttack,
		PhysicalDefense,
		SpecialAttack,
		SpecialDefense,
		Haste,
		CriticalHit
	};
}

float UStatsBlock::BaseStatTotal()
{
	float Ret = 0;
	TArray<UStat*> StatsArray;
	GetStatsArray(StatsArray);
	for(const UStat* Stat : StatsArray)
		if (Stat)
			Ret += Stat->BaseStat;
	return Ret;
}

float UStatsBlock::BaseStatEffectiveAverage()
{

	// Determine if we're using one or both
	const bool bUsePhA = PhysicalAttack->BaseStat > 0.9f * SpecialAttack->BaseStat;
	const bool bUseSpA = SpecialAttack->BaseStat > 0.9f * PhysicalAttack->BaseStat;

	// Get array
	TArray<UStat*> StatsArray;
	GetStatsArray(StatsArray);

	// Count 'em up
	int Count = 0;
	float Total = 0;
	for(UStat* Stat : StatsArray)
	{
		const UPhysicalAttack* PhA = dynamic_cast<UPhysicalAttack*>(Stat);
		const USpecialAttack* SpA = dynamic_cast<USpecialAttack*>(Stat);
		if (PhA)
		{
			if (bUsePhA)
			{
				Total += Stat->BaseStat;
				Count++;
			}
		} else if (SpA)
		{
			if (bUseSpA)
			{
				Total += Stat->BaseStat;
				Count++;
			}
		} else
		{
			Total += Stat->BaseStat;
			Count++;
		}
	}

	// Return
	if (Count==0)
		return 0;
	return Total/Count;
}
