#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "MutationComponent.generated.h"


/**
 * A class for "Mutations" (a la Pokemon natures, but not so boring). These are intrinsic to Monsters.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UMutationComponent : public UEffectComponent
{
	GENERATED_BODY()

public:
	UMutationComponent();

};
