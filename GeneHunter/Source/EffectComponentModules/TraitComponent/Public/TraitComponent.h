#pragma once

#include "IntrinsicEffectComponent.h"

#include "TraitComponent.generated.h"

/**
 * A UEffectComponent that is neither visible to UI nor purgeable. Similar to Pokemon Abilities.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class TRAITCOMPONENT_API UTraitComponent : public UIntrinsicEffectComponent
{
	GENERATED_BODY()

public:

	UTraitComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
