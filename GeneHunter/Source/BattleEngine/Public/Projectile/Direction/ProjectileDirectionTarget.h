#pragma once

#include "CoreMinimal.h"
#include "CombatTargetingComponent.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionTarget.generated.h"

/**
 * The Projectile's direction is set based on a local CombatTargetingComponent. If such a component doesn't exist on the
 * owner, an error is thrown.
 */
UCLASS(ClassGroup=(Projectile), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Projectile direction by targetting a StatsComponent."))
class BATTLEENGINE_API UProjectileDirectionTarget : public UProjectileDirection
{
	GENERATED_BODY()

public:

	virtual void InitializeProjectile(AActor* MoveCaster) override;

	virtual FVector GetDirection() override;
	
protected:

	UPROPERTY()
	UCombatTargetingComponent* TargetingComponent;

private:

	void AssignTargetingComponent();
	
};
