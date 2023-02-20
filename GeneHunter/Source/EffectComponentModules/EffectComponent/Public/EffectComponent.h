#pragma once

#include "CoreMinimal.h"
#include "StackChangeResult.h"
#include "SupportingText.h"
#include "Components/ActorComponent.h"

#include "EffectComponent.generated.h"

/**
 * The root class that is in charge of "effects" (components that attach to Monsters, objects, etc.). The class holds
 * data (e.g., Priority) and code (how effects are actually implemented). Look at the documentation for implementation
 * steps.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	uint16 Stacks = 0;

	/**
	 * If true, the delegate should do nothing (but not be removed). It's up to you to implement this in inherited classes!
	 */
	bool Silenced = false;

public:
	
	virtual bool IsComponentTickEnabled() const override;
	
	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	int32 GetStacks() const;

	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	void SetStacks(const int32 NewStacks);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	void AddStacks(const int32 Amount = 1);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	void RemoveStacks(const int32 Amount = 1);

	/**
	 * The maximum number of times this stacks.
	 *
	 * 1 by default.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual int32 MaxStacks();

	/**
	 * Called whenever stacks are added or the same (but not subtraced), including during OnComponentCreated. For
	 * example, if we're at MaxStacks and another stack is added, the number of stacks doesn't change (we're already at
	 * max), but this is still called.
	 *
	 * Useful for, e.g., HoTs and DoTs to tick immediately when refreshed.
	 *
	 * Does nothing by default.
	 */
	virtual void OnRefreshStacks();

	/**
	 * Called whenever stacks are subtracted (but not added).
	 *
	 * Does nothing by default.
	 */
	virtual void OnReduceStacks();
	
	/**
	 * The lower the priority, the farther away it is from execution. If two priorities are tied, the older effect
	 * is executed first. Order is set externally by EffectsComponent. Order:
	 *
	 *		-	Intrinsic delegates (no Effect attached)
	 *		-	"Before" delegates
	 *			-	Priority 1
	 *			-	Priority 2.a (older)
	 *			-	Priority 2.b (newer)
	 *			-	...
	 *		-	[Function executes]
	 *		-	"After" delegates
	 *			-	...
	 *			-	Priority 2.b (newer)
	 *			-	Priority 2.a (older)
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
	virtual FText GetDisplayName();

	/**
	 * If true, the effect is not removed when switching out. Default is true.
	 *
	 * Ex: in Pokemon, Paralysis is persistent but Confusion is not.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual bool IsPersistent() const;
	
	/**
	 * If true, the delegate should do nothing (but not be removed).
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual bool IsSilenced() const;

	/**
	 * Sets Silence to true. Should do other things as well in the inherited classes.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	virtual void Silence();

	/**
	 * Sets Silence to false. Should do other things as well in the inherited classes.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	virtual void Unsilence();

	/**
	 * If true, the UI should somehow render this. Note: the responsibility of doing so is not upon this module.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual bool IsVisibleToUI() const;

	/**
	 * If true, it is possible to reduce the number of stacks via UEffectComponent::Purge. Stacks may always be removed
	 * via code regardless of this value.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual bool IsPurgeable() const;

	/**
	 * "Purges" this UEffectComponent, reducing Stacks by the given amount. However, if the UEffectComponent is not a
	 * Purgeable class, this does nothing (that is, if IsPurgeable returns false, this does nothing). Stacks may always
	 * be removed via code regardless of IsPurgeable and this function.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	virtual EStackChangeResult Purge(const int32 Amount = 1);

	/**
	 * Sets stacks to 1. It is here that you should bind your delegate by using macros like SEARCH_FOR_COMPONENT.
	 */
	virtual void OnComponentCreated() override;
	
};
