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

	UTimedEffectComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
