#include "Effects/ModifyStat.h"

void FModifyStat::OnAttach()
{

	// Trigger on RecalculateStats
	if (Trigger == ETrigger::RecalculateStats || Trigger == ETrigger::Both)
	{
		RecalculateStatsDelegate.BindLambda(RecalculateLambda);
		StatsComponent->AfterRecalculateStatsArray.Add(RecalculateStatsDelegate);
	}

	// Trigger on ModifyStats
	if (Trigger == ETrigger::ModifyStats || Trigger == ETrigger::Both)
	{
		ModifyStatDelegate.BindLambda(ModifyLambda);
		StatsComponent->AfterModifyStatArray.Add(ModifyStatDelegate);
	}

}

void FModifyStat::OnDetach()
{
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
