#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "MutationComponent_BaseClass.generated.h"


/**
 * A class for "Mutations" (a la Pokemon natures, but not so boring). These are intrinsic to Monsters.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UMutationComponent_BaseClass : public UEffectComponent
{
	GENERATED_BODY()

public:
	UMutationComponent_BaseClass();

};
