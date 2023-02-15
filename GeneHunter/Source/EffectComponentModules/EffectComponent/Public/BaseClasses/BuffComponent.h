#pragma once

#include "CoreMinimal.h"
#include "TimedEffectComponent.h"
#include "BuffComponent.generated.h"


/**
 * A class for positive TimedEffectComponents.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UBuffComponent : public UTimedEffectComponent
{
	GENERATED_BODY()

};
