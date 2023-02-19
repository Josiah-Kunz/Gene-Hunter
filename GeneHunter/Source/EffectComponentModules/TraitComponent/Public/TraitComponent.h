#pragma once

#include "IntrinsicEffectComponent.h"

#include "TraitComponent.generated.h"

/**
 * A UIntrinsicEffectComponent that is randomly assigned to a Monster from a pool. The pool depends on the UType of the
 * Monster. Similar to Pokemon Abilities.
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
