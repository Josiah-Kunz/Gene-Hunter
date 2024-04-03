#pragma once

#include "EffectComponent.h"

#include "TimedEffectComponent.generated.h"

/**
 * A UEffectComponent that has a set duration, is visible to UI, and is purgeable.
 *
 * Suitable for both static effects (such as +50% PhA for 5 seconds) and dynamic effects (such as healing 1% per second
 * for 5 seconds).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class TIMEDEFFECTCOMPONENT_API UTimedEffectComponent : public UEffectComponent
{
	GENERATED_BODY()

public:
	
	/**
	 * Time until this effect expires.
	 */
	float RemainingTime;

	/**
	 * When RemainingTime <= NextModTime, the stat will be modified.
	 */
	float NextModTime = -1;

	/**
	 * Determines whether additional stacks set RemainingTime back to StartingDuration or not. Default is true.
	 */
	bool bStacksRefreshDuration = true;

	UTimedEffectComponent();

	/**
	 * How often the effect occurs (in seconds). If there's no dynamic effect, this parameter doesn't matter.
	 */
	virtual float TickDuration();;

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;

	virtual void OnRefreshStacks() override;
	
	/**
	 * The duration of this effect when it is first applied.
	 */
	virtual float StartingDuration();

	/**
	 * Sets RemainingTime to StartingDuration.
	 */
	virtual void OnComponentCreated() override;

	/**
	 * Ticks RemainingTime down.
	 */
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

	/**
	 * Called whenever the component is created, when stacks are refreshed, during TickComponent, and when the timer
	 * runs out.
	 *
	 * Does nothing by default.
	 */
	virtual void DoEffect();

};