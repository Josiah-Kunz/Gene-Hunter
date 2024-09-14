#pragma once

#include "AuraComponent.h"

#include "PositiveAuraComponent.generated.h"

/**
 * A "good" UAura.
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class POSITIVEAURACOMPONENT_API UPositiveAuraComponent : public UAuraComponent
{
	GENERATED_BODY()

public:

	UPositiveAuraComponent();
};
