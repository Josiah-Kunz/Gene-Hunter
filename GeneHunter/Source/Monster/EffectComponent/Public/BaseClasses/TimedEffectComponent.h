#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "TimedEffectComponent.generated.h"


/**
 * A class for EffectComponents that expire after a certain time. Stackable. This is the base class; you should use 
 *	UBuffComponent or UDebuffComponent.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UTimedEffectComponent : public UEffectComponent
{
	GENERATED_BODY()

public:

	/**
	 * Time until this effect expires.
	 */
	float RemainingTime;

	float Stacks;

	UTimedEffectComponent();
	
	/**
	 * The duration of this effect when it is first applied.
	 */
	virtual float StartingDuration();

	/**
	 * The maximum number of times this stacks.
	 */
	virtual int MaxStacks();

	/**
	 * Sets RemainingTime to StartingDuration.
	 */
	virtual void OnComponentCreated() override;

	/**
	 * Ticks RemainingTime down.
	 */
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

};
