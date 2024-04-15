#pragma once

#include "IntrinsicEffectComponent.h"

#include "MutationEffectComponent.generated.h"

/**
 * A UIntrinsicEffectComponent that is randomly assigned to a Monster from a pool. The pool depends on the species of
 * Monster. Similar to Pokemon Natures.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class MUTATIONEFFECTCOMPONENT_API UMutationEffectComponent : public UIntrinsicEffectComponent
{
	GENERATED_BODY()
};
