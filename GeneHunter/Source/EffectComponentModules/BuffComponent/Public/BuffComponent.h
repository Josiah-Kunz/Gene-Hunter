#pragma once

#include "TimedEffectComponent.h"

#include "BuffComponent.generated.h"

/**
 * A UEffectComponent that is neither visible to UI nor purgeable. Similar to Pokemon Abilities.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class BUFFCOMPONENT_API UBuffComponent : public UTimedEffectComponent
{
	GENERATED_BODY()

public:

	UBuffComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
