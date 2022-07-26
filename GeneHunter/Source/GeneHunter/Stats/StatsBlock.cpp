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

void UStatsBlock::SetLevel(const int Value)
{
	Level = Value;
	TArray<FStat> StatsArray;
	GetStatsArray(StatsArray);
	for(FStat& Stat : StatsArray)
		Stat.Update(Level);
}

void UStatsBlock::RandomizeStats(
	const int MinBaseStat, const int MaxBaseStat,
	const int MinBasePairs, const int MaxBasePairs)
{
	TArray<FStat> StatsArray;
	GetStatsArray(StatsArray);
	for(FStat& Stat : StatsArray)
	{
		if (MaxBaseStat > MinBaseStat)
			Stat.BaseStat = FMath::RandRange(MinBaseStat, MaxBaseStat);
		if (MaxBasePairs > MinBasePairs)
			Stat.BasePairs = FMath::RandRange(MinBasePairs, MaxBasePairs);
		Stat.Update(Level);
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



void UStatsBlock::ModifyStats(TArray<FStatModStruct>& ValueMap, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(FStatModStruct& StatMod : ValueMap)
		StatMod.Stat.ModifyValue(StatMod.Mod, ValueType, Mode);
}

void UStatsBlock::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	TArray<FStat> StatsArray;
	GetStatsArray(StatsArray);
	for(FStat& Stat :StatsArray)
		Stat.ModifyValue(UniformMod, ValueType, Mode);
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
	
	TArray<FStat> StatsArray, OtherStatsArray;
	GetStatsArray(StatsArray);
	Other->GetStatsArray(OtherStatsArray);
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(StatsArray[i].GetCurrentValue() - OtherStatsArray[i].GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(StatsArray[i].GetPermanentValue() - OtherStatsArray[i].GetPermanentValue() > Tolerance))
				return false;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UStatsBlock::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}


void UStatsBlock::GetStatsArray(TArray<FStat>& Stats)
{
	Stats = {
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
	TArray<FStat> StatsArray;
	GetStatsArray(StatsArray);
	for(const FStat& Stat : StatsArray)
		Ret += Stat.BaseStat;
	return Ret;
}

float UStatsBlock::BaseStatEffectiveAverage()
{

	// Determine if we're using one or both
	const bool bUsePhA = PhysicalAttack.BaseStat > 0.9f * SpecialAttack.BaseStat;
	const bool bUseSpA = SpecialAttack.BaseStat > 0.9f * PhysicalAttack.BaseStat;

	// Count 'em up
	int Count = 0;
	float Total = 0;
	TArray<FStat> StatsArray;
	GetStatsArray(StatsArray);
	for(FStat Stat : StatsArray)
	{
		/*
		const FPhysicalAttack* PhA = dynamic_cast<FPhysicalAttack>(Stat);
		const FSpecialAttack* SpA = dynamic_cast<FSpecialAttack>(Stat);
		*/

		if (FPhysicalAttack* PhA = static_cast<FPhysicalAttack*>(&Stat))
		{
			if (bUsePhA)
			{
				Total += Stat.BaseStat;
				Count++;
			}
		/*} else if (Cast<FSpecialAttack>(&Stat))
		{
			if (bUseSpA)
			{
				Total += Stat.BaseStat;
				Count++;
			}
			*/
		} else
		{
			Total += Stat.BaseStat;
			Count++;
		}
	}

	// Return
	if (Count==0)
		return 0;
	return Total/Count;
}
