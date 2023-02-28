#pragma once

#include "CoreMinimal.h"
#include "Invulnerable.h"
#include "DimensionalShift.generated.h"

/**
 * Same as Invulnerable (just with a different name for, e.g., UType flavor).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class BUFFCOMPONENT_API UDimensionalShift : public UInvulnerable
{
	GENERATED_BODY()

};

