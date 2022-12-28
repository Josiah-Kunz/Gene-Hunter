#pragma once

#include "CoreMinimal.h"

#include "Effect.generated.h"

/**
 * A struct to hold data (e.g., Priority) and code (how effects are actually implemented). Implementation of this data
 *	happens in EffectsComponent.
 */
USTRUCT(Blueprintable)
struct EFFECTS_API FEffect
{
	GENERATED_BODY()

public:
	
	virtual ~FEffect() = default;

public:

	/**
	 * The lower the priority, the farther away it is from execution. If two priorities are tied, the execution order is
	 * randomized. Order is set externally by EffectsComponent. Order:
	 *
	 *		-	Intrinsic delegates (no Effect attached)
	 *		-	"Before" delegates
	 *			-	Priority 1
	 *			-	Priority 2
	 *			-	...
	 *		-	[Function executes]
	 *		-	"After" delegates
	 *			-	...
	 *			-	Priority 2
	 *			-	Priority 1
	 *		-	Intrinsic delegates
	 * 
	 */
	virtual float GetPriority(){return 50;}

	/**
	 * Called by EffectsComponent when this Effect is first attached to an EffectsComponent. Here, you should add
	 * delegates to delegate arrays in EffectableComponents. For example, for the "Adamant" effect:
	 *
	 *		- Delegate => UStatsComponent::FRecalculateStatsDelegate Adamant;
	 *		- Define => Adamant.BindLambda(...);
	 *		- Attach => StatsComponent->AfterRecalculateStatsArray.Add(Adamant);
	 */
	virtual void OnAttach();

	/**
	* Called by EffectsComponent when this Effect is first detached from an EffectsComponent. Here, you should remove
	 * delegates from delegate arrays in EffectableComponents. For example, for the "Adamant" effect:
	 *
	 *		- StatsComponent->AfterRecalculateStatsArray.Remove(Adamant);
	 */
	virtual void OnDetach();
	
};
