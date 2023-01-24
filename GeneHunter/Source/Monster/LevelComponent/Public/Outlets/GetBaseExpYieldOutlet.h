#pragma once
#include "DelegateClasses/GetBaseExpYieldDelegate.h"

#include "GetBaseExpYieldOutlet.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FGetBaseExpYieldOutlet
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TArray<FGetBaseExpYieldDelegate> Before;

	UPROPERTY()
	TArray<FGetBaseExpYieldDelegate> After;

public:

	/**
	 * Executes all delegates in Before.
	 */
	void ExecuteBefore(float& BaseExp)
	{
		for(FGetBaseExpYieldDelegate BeforeDelegate : Before)
		{
			BeforeDelegate.Delegate.Execute(BaseExp);
		}	
	};

	/**
	 * Executes all delegates in After.
	 */
	void ExecuteAfter(float& BaseExp)
	{
		for(FGetBaseExpYieldDelegate AfterDelegate : After)
		{
			AfterDelegate.Delegate.Execute(BaseExp);
		}	
	};

	/**
	 * Adds a delegate to the "before execution" array at the correct (sorted) index based on priority.
	 */
	void AddDelegateBefore(const FGetBaseExpYieldDelegate DelegateToAdd, const float Priority)
	{
		bool bAdded = false;
		for(int i=0; i<Before.Num();i++)
		{
			if (Priority > Before[i].Priority)
			{
				Before.Insert(DelegateToAdd, i);
				bAdded = true;
				break;
			}
		}
		if (!bAdded)
		{
			Before.Add(DelegateToAdd);
		}
	};

	/**
	 * Adds a delegate to the "after execution" array at the correct (sorted) index based on priority.
	 */
	void AddDelegateAfter(const FGetBaseExpYieldDelegate DelegateToAdd, const float Priority)
	{
		bool bAdded = false;
		for(int i=0; i<After.Num();i++)
		{
			if (Priority < After[i].Priority)
			{
				After.Insert(DelegateToAdd, i);
				bAdded = true;
				break;
			}
		}
		if (!bAdded)
		{
			After.Add(DelegateToAdd);
		}
	};
	
};
