#include "Effects/PositiveStatAura.h"
#include "ComponentUtilities.h"

UPositiveStatAura::UPositiveStatAura()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPositiveStatAura::AssignData(FStat* NewStat, const float NewValue, const EModificationMode NewMode,
                                   const EStatValueType NewValueType, const EStatModifierTrigger NewTrigger)
{
	Stat = NewStat;
	Value = NewValue;
	Mode = NewMode;
	ValueType = NewValueType;
	Trigger = NewTrigger;
}

void UPositiveStatAura::OnComponentCreated()
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

void UPositiveStatAura::OnComponentDestroyed(bool bDestroyingHierarchy)
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