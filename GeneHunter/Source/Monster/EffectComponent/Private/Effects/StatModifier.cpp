#include "Effects/StatModifier.h"
#include "EffectUtilities.h"

void UStatModifier::OnComponentCreated()
{
	Super::OnComponentCreated();

	REQUIRE_COMPONENT(UStatsComponent, StatsComponent, GetOwner())
	
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
}
