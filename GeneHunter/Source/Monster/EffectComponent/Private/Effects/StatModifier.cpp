#include "Effects/StatModifier.h"
#include "EffectUtilities.h"

void UStatModifier::OnComponentCreated()
{
	Super::OnComponentCreated();
	UE_LOG(LogTemp, Warning, TEXT("Created"))
	REQUIRE_COMPONENT(UStatsComponent, StatsComponent, GetOwner())
	UE_LOG(LogTemp, Warning, TEXT( "%s"), StatsComponent == nullptr ? "Null" : "Not null")
	// Trigger on RecalculateStats
	if (Trigger == EStatModifierTrigger::RecalculateStats || Trigger == EStatModifierTrigger::Both)
	{
		RecalculateStatsDelegate.BindLambda(RecalculateLambda);
		StatsComponent->AfterRecalculateStatsArray.Add(RecalculateStatsDelegate);
	}

	// Trigger on ModifyStats
	if (Trigger == EStatModifierTrigger::ModifyStats || Trigger == EStatModifierTrigger::Both)
	{
		ModifyStatDelegate.BindLambda(ModifyLambda);
		StatsComponent->AfterModifyStatArray.Add(ModifyStatDelegate);
	}
}

void UStatModifier::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	auto RecalculateStatsArray = StatsComponent->AfterRecalculateStatsArray;
	for(int i=RecalculateStatsArray.Num() - 1; i>=0; i--)
	{
		if (RecalculateStatsArray[i].GetHandle() == RecalculateStatsDelegate.GetHandle())
		{
			StatsComponent->AfterRecalculateStatsArray.RemoveAt(i);
			break;
		}
	}
	
	auto ModifyStatArray = StatsComponent->AfterModifyStatArray;
	for(int i=ModifyStatArray.Num() - 1; i>=0; i--)
	{
		if (ModifyStatArray[i].GetHandle() == ModifyStatDelegate.GetHandle())
		{
			StatsComponent->AfterModifyStatArray.RemoveAt(i);
			break;
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Has been destroyed"))
}

void UStatModifier::InitializeComponent()
{
	Super::InitializeComponent();
	UE_LOG(LogTemp, Warning, TEXT("Has been initialized"))
}

void UStatModifier::OnRegister()
{
	Super::OnRegister();
	UE_LOG(LogTemp, Warning, TEXT("Has been registered"))
}

void UStatModifier::PostApplyToComponent()
{
	Super::PostApplyToComponent();
	UE_LOG(LogTemp, Warning, TEXT("Has been PostApplyToComponent"))
}

void UStatModifier::RegisterComponentTickFunctions(bool bRegister)
{


	Super::RegisterComponentTickFunctions(bRegister);

	UE_LOG(LogTemp, Warning, TEXT("Has been RegisterTick"))
}

bool UStatModifier::ReplicateSubobjects(UActorChannel* Channel, FOutBunch* Bunch, FReplicationFlags* RepFlags)
{

	UE_LOG(LogTemp, Warning, TEXT("Has been ReplicateSubobjects"))
	return Super::ReplicateSubobjects(Channel, Bunch, RepFlags);

	
}

void UStatModifier::SetActive(bool bNewActive, bool bReset)
{
	Super::SetActive(bNewActive, bReset);

	UE_LOG(LogTemp, Warning, TEXT("Has been set active"))
}
