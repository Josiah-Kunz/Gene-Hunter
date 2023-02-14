#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "NegativeAuraComponent_BaseClass.generated.h"


/**
 * A class for negative auras (negative effects that do not expire).
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UNegativeAuraComponent_BaseClass : public UEffectComponent
{
	GENERATED_BODY()

	UNegativeAuraComponent_BaseClass();

};
