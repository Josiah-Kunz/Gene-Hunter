#include "StatsBlock.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UStatsBlock::UStatsBlock()
{
	PrimaryComponentTick.bCanEverTick = false;
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

