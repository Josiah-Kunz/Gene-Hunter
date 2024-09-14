#pragma once

#include "TimedEffectComponent.h"

#include "BuffComponent.generated.h"

/**
 * A UTimedEffectComponent that is "good".
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class BUFFCOMPONENT_API UBuffComponent : public UTimedEffectComponent
{
	GENERATED_BODY()

public:

	UBuffComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;

	virtual bool IsPersistent() const override;
};
