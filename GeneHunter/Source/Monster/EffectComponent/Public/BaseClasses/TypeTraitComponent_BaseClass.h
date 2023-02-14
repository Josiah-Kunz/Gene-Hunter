#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "TypeTraitComponent_BaseClass.generated.h"


/**
 * A class for "elemental traits" that Monster have based on their Types.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UTypeTraitComponent_BaseClass : public UEffectComponent
{
	GENERATED_BODY()

public:
	UTypeTraitComponent_BaseClass();

};
