#pragma once

#include "EffectComponent.h"

#include "AuraComponent.generated.h"

/**
 * A class to hold data (e.g., Priority) and code (how effects are actually implemented). Look at the documentation
 * for implementation steps.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class AURACOMPONENT_API UAuraComponent : public UEffectComponent
{
	GENERATED_BODY()
	
};
