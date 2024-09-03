#pragma once

#include "CoreMinimal.h"
#include "CombatTargetingComponent.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionVector.generated.h"

/**
 * The Projectile's direction is set based on a local CombatTargetingComponent. If such a component doesn't exist on the
 * owner, an error is thrown.
 */
UCLASS(ClassGroup=(Projectile), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Projectile direction by vector."))
class BATTLEENGINE_API UProjectileDirectionVector : public UProjectileDirection
{
	GENERATED_BODY()

public:

	virtual FVector GetDirection() override;

private:

	UPROPERTY()
	UCombatTargetingComponent* TargetingComponent;
};
