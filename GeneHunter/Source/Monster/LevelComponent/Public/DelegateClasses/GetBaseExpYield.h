#pragma once

#include "CoreMinimal.h"

#include "GetBaseExpYield.generated.h"

/**
 * Parameters:
 *	- A copy of base exp yield to be returned by ULevelComponent::GetBaseExpYield().
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FDGetBaseExpYield
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegate, float&, BaseExp);

	/**
	 * Executes all delegates in BeforeMap.
	 */
	void ExecuteBefore (float& BaseExp);

	/**
	 * Executes all delegates in AfterMap.
	 */
	void ExecuteAfter (float& BaseExp);

	/**
	 * Adds a delegate to the "before execution" array at the correct (sorted) index based on priority.
	 */
	void AddDelegateBefore(const FDelegate DelegateToAdd, const float Priority);

	/**
	 * Adds a delegate to the "after execution" array at the correct (sorted) index based on priority.
	 */
	void AddDelegateAfter(const FDelegate DelegateToAdd, const float Priority);

private:
	
	/**
	 * The delegates that should be called before the main execution. Map is sorted by priority. Priority is
	 * UEffectComponent::GetPriority().
	 */
	UPROPERTY()
	TMap<FDelegate, float> BeforeMap;

	/**
	 * The delegates that should be called after the main execution. Map is sorted by priority. Priority is
	 * UEffectComponent::GetPriority().
	 */
	UPROPERTY()
	TMap<FDelegate, float> AfterMap;
	
};
