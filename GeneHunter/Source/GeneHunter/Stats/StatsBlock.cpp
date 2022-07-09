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


void UStatsBlock::ModifyStats(TMap<UStat*, int>& ValueMap, const EStatGainType GainType, const EModificationMode Mode)
{
	// Guard
	if (!CheckGainsNum(ValueMap.Num()))
		return;

	// Keys
	TArray<UStat*> StatsArray;
	ValueMap.GetKeys(StatsArray);
	
	// Add stats
	for(int i=0; i<ValueMap.Num(); i++)
		StatsArray[i]->ModifyValue(ValueMap[StatsArray[i]], GainType, Mode);
}

bool UStatsBlock::CheckGainsNum(const int Length)
{
	TArray<UStat*> Array;
	StatsArray(Array);
	
	if (Length == Array.Num())
		return true;

	UE_LOG(LogTemp, Error, TEXT("Attempted %s Stat gains, but found %s Stats!"),
		*FString::FromInt(Length),
		*FString::FromInt(Array.Num()));
	return false;
}


void UStatsBlock::StatsArray(TArray<UStat*>& Array)
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
