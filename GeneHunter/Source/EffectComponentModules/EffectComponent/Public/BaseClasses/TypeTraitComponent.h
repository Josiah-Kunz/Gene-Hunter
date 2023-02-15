#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "TypeTraitComponent.generated.h"


/**
 * A class for "elemental traits" that Monster have based on their Types.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UTypeTraitComponent : public UEffectComponent
{
	GENERATED_BODY()

public:
	UTypeTraitComponent();

};
