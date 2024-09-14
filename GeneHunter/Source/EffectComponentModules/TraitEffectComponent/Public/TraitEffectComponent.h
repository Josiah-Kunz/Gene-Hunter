#pragma once

#include "IntrinsicEffectComponent.h"

#include "TraitEffectComponent.generated.h"

/**
 * A UIntrinsicEffectComponent that is randomly assigned to a Monster from a pool. The pool depends on the UType of the
 * Monster. Similar to Pokemon Abilities.
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class TRAITEFFECTCOMPONENT_API UTraitEffectComponent : public UIntrinsicEffectComponent
{
	GENERATED_BODY()
};
