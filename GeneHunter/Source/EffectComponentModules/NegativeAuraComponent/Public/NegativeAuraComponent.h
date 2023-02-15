#pragma once

#include "AuraComponent.h"

#include "NegativeAuraComponent.generated.h"

/**
 * A "bad" UAura.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class NEGATIVEAURACOMPONENT_API UNegativeAuraComponent : public UAuraComponent
{
	GENERATED_BODY()

public:

	UNegativeAuraComponent();
};
