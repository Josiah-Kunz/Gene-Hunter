#pragma once

#include "EffectComponent.h"

#include "IntrinsicEffectComponent.generated.h"

/**
 * A UEffectComponent that is neither visible to UI nor purgeable. Think of Pokemon Abilities or Natures.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class INTRINSICEFFECTCOMPONENT_API UIntrinsicEffectComponent : public UEffectComponent
{
	GENERATED_BODY()

public:

	UIntrinsicEffectComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
