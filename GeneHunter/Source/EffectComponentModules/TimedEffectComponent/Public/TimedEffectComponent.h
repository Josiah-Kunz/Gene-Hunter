#pragma once

#include "EffectComponent.h"

#include "TimedEffectComponent.generated.h"

/**
 * A UEffectComponent that has a set duration, is visible to UI, and is purgeable.
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

	UTimedEffectComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
	
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

};