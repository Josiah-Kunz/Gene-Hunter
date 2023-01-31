#pragma once

#include "CoreMinimal.h"
#include "SupportingText.h"
#include "Components/ActorComponent.h"

#include "EffectComponent.generated.h"

/**
 * A class to hold data (e.g., Priority) and code (how effects are actually implemented). Add to an Actor via UEffectComponent::ApplyEffect(Actor).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UEffectComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	uint16 Stacks = 0;

public:

	UEffectComponent();


	virtual bool IsComponentTickEnabled() const override;
	
	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	int32 GetStacks();

	/**
	 * When an EffectComponent is attached to an Actor, it looks for duplicate EffectComponents. If such a duplicate
	 * exists, it increases the number of Stacks (up to MaxStacks) rather than attaching a new EffectComponent.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent")
	void SetStacks(const int32 NewStacks);

	/**
	 * The maximum number of times this stacks.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="EffectComponent", BlueprintPure)
	virtual int32 MaxStacks();

	virtual void OnRefreshStacks();
	
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
	 * Sets stacks to 1.
	 */
	virtual void OnComponentCreated() override;
	
};
