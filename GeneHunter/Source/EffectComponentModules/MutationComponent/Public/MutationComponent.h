#pragma once

#include "IntrinsicEffectComponent.h"

#include "MutationComponent.generated.h"

/**
 * A UIntrinsicEffectComponent that is randomly assigned to a Monster from a pool. The pool depends on the species of
 * Monster. Similar to Pokemon Natures.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class MUTATIONCOMPONENT_API UMutationComponent : public UIntrinsicEffectComponent
{
	GENERATED_BODY()

public:

	UMutationComponent();

	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
