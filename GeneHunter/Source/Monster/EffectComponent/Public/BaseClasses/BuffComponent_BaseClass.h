#pragma once

#include "CoreMinimal.h"
#include "TimedEffectComponent_BaseClass.h"
#include "BuffComponent_BaseClass.generated.h"


/**
 * A class for positive TimedEffectComponents.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UBuffComponent_BaseClass : public UTimedEffectComponent_BaseClass
{
	GENERATED_BODY()

};
