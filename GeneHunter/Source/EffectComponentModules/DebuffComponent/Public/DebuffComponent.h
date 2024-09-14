#pragma once

#include "TimedEffectComponent.h"

#include "DebuffComponent.generated.h"

/**
 * A UTimedEffectComponent that is "bad".
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class DEBUFFCOMPONENT_API UDebuffComponent : public UTimedEffectComponent
{
	GENERATED_BODY()

public:

	UDebuffComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
