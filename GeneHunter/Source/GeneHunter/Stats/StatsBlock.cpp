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


void UStatsBlock::GainStats(TMap<UStat*, int>& Gains, const EStatGainMode Mode)
{
	// Guard
	if (!CheckGainsNum(Gains.Num()))
		return;

	// Keys
	TArray<UStat*> StatsArray;
	Gains.GetKeys(StatsArray);
	
	// Add stats
	for(int i=0; i<Gains.Num(); i++)
	{
		switch(Mode)
		{
		case EStatGainMode::Current:
			StatsArray[i]->SetCurrentValue(StatsArray[i]->GetCurrentValue() + Gains[StatsArray[i]]);
			break;
		case EStatGainMode::Permanent:
			StatsArray[i]->SetPermanentValue(StatsArray[i]->GetPermanentValue() + Gains[StatsArray[i]]);
			break;
		case EStatGainMode::CurrentAndPermanent:
			StatsArray[i]->SetPermanentValue(StatsArray[i]->GetPermanentValue() + Gains[StatsArray[i]]);
			StatsArray[i]->SetCurrentValue(StatsArray[i]->GetCurrentValue() + Gains[StatsArray[i]]);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Mode not coded for in StatsBlock::GainStats! Fix ASAP!"));
			break;
		}
	}
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
		&Health,
		&PhysicalAttack,
		&PhysicalDefense,
		&SpecialAttack,
		&SpecialDefense,
		&Haste,
		&CriticalHit
	};
}
