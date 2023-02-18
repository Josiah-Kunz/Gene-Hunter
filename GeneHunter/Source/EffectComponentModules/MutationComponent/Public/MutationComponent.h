#pragma once

#include "IntrinsicEffectComponent.h"

#include "MutationComponent.generated.h"

/**
 * A UEffectComponent that is neither visible to UI nor purgeable. Similar to Pokemon Abilities.
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
