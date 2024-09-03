#pragma once

#include "CoreMinimal.h"
#include "ProjectileDependent.h"
#include "ProjectileSpeed.generated.h"

/**
 * Base class for controlling Projectile speed.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UProjectileSpeed : public UProjectileDependent
{
	GENERATED_BODY()

public:

	// Sets default values for this component's properties
	UProjectileSpeed();

	virtual void InitializeProjectile(AActor* MoveCaster) override;

};
