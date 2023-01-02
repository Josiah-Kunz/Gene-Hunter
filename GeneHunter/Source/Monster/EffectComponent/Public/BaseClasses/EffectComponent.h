#pragma once

#include "CoreMinimal.h"
#include "StatsComponent.h"
#include "SupportingText.h"
#include "Components/ActorComponent.h"

#include "EffectComponent.generated.h"

/**
 * A struct to hold data (e.g., Priority) and code (how effects are actually implemented). Implementation of this data
 *	happens in EffectsComponent.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	int Stacks = 1;

public:
	
	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	int GetStacks();

	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	void SetStacks(const int NewStacks);

	/**
	 * The maximum number of times this stacks.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual int MaxStacks();
	
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
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual float GetPriority();

	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual FSupportingText GetSupportingText();

	/**
	 * How this EffectComponent will be displayed in the UI. Defaults to class name (minus the "U") split by camel case.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual FText GetName();

	/**
	 * Retries the UStatsComponent.
	 */
	virtual void OnComponentCreated() override;

	virtual void OnRegister() override;
	
};
