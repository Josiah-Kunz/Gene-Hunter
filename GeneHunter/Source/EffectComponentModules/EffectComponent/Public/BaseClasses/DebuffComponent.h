#pragma once

#include "CoreMinimal.h"
#include "TimedEffectComponent.h"
#include "DebuffComponent.generated.h"


/**
 * A class for negative TimedEffectComponents.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDebuffComponent : public UTimedEffectComponent
{
	GENERATED_BODY()

};
