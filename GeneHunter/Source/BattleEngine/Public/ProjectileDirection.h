#pragma once

#include "CoreMinimal.h"
#include "ProjectileDependent.h"
#include "UObject/Object.h"
#include "ProjectileDirection.generated.h"

/**
 * Base class to drive the Projectile's velocity direction.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UProjectileDirection : public UProjectileDependent
{
	GENERATED_BODY()

public:
	/**
	 * The direction that the projectile goes. Override this!
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual FVector GetDirection() PURE_VIRTUAL(UProjectileTarget::GetTargetDirection, return FVector::ZeroVector;);

	/**
	 * Sets the direction of the projectile's velocity. Normalizes the direction first. Use this whenever you're ready
	 * (e.g., in BeginPlay or Tick).
	 */
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual void ApplyDirection();

	/**
	 * Calls SetDirection for the first frame. Called by ProjectileMove.
	 */
	virtual void InitializeProjectile() override;
};
