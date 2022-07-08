#include "StatsBlock.h"

#include "CrashReportCore/Public/Android/AndroidErrorReport.h"

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

void UStatsBlock::GainStats(TArray<int>& Gains, const EStatGainMode Mode)
{

	// Construct Map
	TArray<UStat*> Array;
	StatsArray(Array);
	GainStatsInternal(Array, Gains, Mode);
	
}

void UStatsBlock::GainStats(const TMap<UStat*, int> Gains, const EStatGainMode Mode)
{
	TArray<UStat*> StatsArray;
	TArray<int> GainsArray;
	Gains.GetKeys(StatsArray);
	Gains.GenerateValueArray(GainsArray);
	GainStatsInternal(StatsArray, GainsArray, Mode);
}

void UStatsBlock::GainStatsInternal(TArray<UStat*>& StatsArray, TArray<int>& Gains, const EStatGainMode Mode)
{

	// Guard
	if (!CheckGainsNum(StatsArray.Num()) || !CheckGainsNum(Gains.Num()))
		return;

	// Add stats
	for(int i=0; i<Gains.Num(); i++)
	{
		switch(Mode)
		{
		case EStatGainMode::Current:
			StatsArray[i]->SetCurrentValue(StatsArray[i]->GetCurrentValue() + Gains[i]);
			break;
		case EStatGainMode::Permanent:
			StatsArray[i]->SetPermanentValue(StatsArray[i]->GetPermanentValue() + Gains[i]);
			break;
		case EStatGainMode::CurrentAndPermanent:
			StatsArray[i]->SetPermanentValue(StatsArray[i]->GetPermanentValue() + Gains[i]);
			StatsArray[i]->SetCurrentValue(StatsArray[i]->GetCurrentValue() + Gains[i]);
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("Mode not coded for in StatsBlock::GainStatsInternal! Fix ASAP!"));
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
