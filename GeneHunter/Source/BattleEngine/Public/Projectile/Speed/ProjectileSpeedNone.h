#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpeed.h"
#include "ProjectileSpeedNone.generated.h"

/**
 * Does nothing.
 */
UCLASS()
class BATTLEENGINE_API UProjectileSpeedNone : public UProjectileSpeed
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UProjectileSpeedNone();

};
