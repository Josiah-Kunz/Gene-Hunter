#include "DelegateClasses/GetBaseExpYield.h"

void FDGetBaseExpYield::ExecuteBefore(float& BaseExp)
{
	for(TPair<FDelegate, float>& Pair : BeforeMap) 
	{ 
		Pair.Key.Execute(BaseExp); 
	}
}

void FDGetBaseExpYield::ExecuteAfter(float& BaseExp)
{
	for(TPair<FDelegate, float>& Pair : AfterMap) 
	{ 
		Pair.Key.Execute(BaseExp); 
	}
}

void FDGetBaseExpYield::AddDelegateBefore(const FDelegate DelegateToAdd, const float Priority)
{
	BeforeMap.Add(DelegateToAdd, Priority);
	BeforeMap.ValueSort([](const float PriorityA, const float PriorityB)
	{
		return PriorityA > PriorityB;
	});
}

void FDGetBaseExpYield::AddDelegateAfter(const FDelegate DelegateToAdd, const float Priority)
{
	AfterMap.Add(DelegateToAdd, Priority);
	AfterMap.ValueSort([](const float PriorityA, const float PriorityB)
	{
		return PriorityA < PriorityB;
	});
}
