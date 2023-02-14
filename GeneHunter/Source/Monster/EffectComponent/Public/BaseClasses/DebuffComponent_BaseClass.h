#pragma once

#include "CoreMinimal.h"
#include "TimedEffectComponent_BaseClass.h"
#include "DebuffComponent_BaseClass.generated.h"


/**
 * A class for negative TimedEffectComponents.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDebuffComponent_BaseClass : public UTimedEffectComponent_BaseClass
{
	GENERATED_BODY()

};
