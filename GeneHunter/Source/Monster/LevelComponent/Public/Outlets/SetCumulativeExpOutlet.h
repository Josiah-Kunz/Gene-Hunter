#pragma once
#include "DelegateClasses/SetCumulativeExpDelegate.h"

#include "SetCumulativeExpOutlet.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCumulativeExpOutlet
{
	GENERATED_BODY()

private:

	UPROPERTY()
	TArray<FSetCumulativeExpWrapper> Before;

	UPROPERTY()
	TArray<FSetCumulativeExpWrapper> After;

public:

	/**
	 * Executes all delegates in Before.
	 */
	void ExecuteBefore(const int CurrentCXP, int& AttemptedCXP)
	{
		for(FSetCumulativeExpWrapper BeforeDelegate : Before)
		{
			BeforeDelegate.Delegate.Execute(CurrentCXP, AttemptedCXP);
		}	
	};

	/**
	 * Executes all delegates in After.
	 */
	void ExecuteAfter(const int CurrentCXP, int& AttemptedCXP)
	{
		for(FSetCumulativeExpWrapper AfterDelegate : After)
		{
			AfterDelegate.Delegate.Execute(CurrentCXP, AttemptedCXP);
		}	
	};

	/**
	 * Adds a delegate to the "before execution" array at the correct (sorted) index based on priority.
	 */
	void AddDelegateBefore(const FSetCumulativeExpWrapper DelegateToAdd, const float Priority)
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
	void AddDelegateAfter(const FSetCumulativeExpWrapper DelegateToAdd, const float Priority)
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
