#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirectionTarget.h"
#include "ProjectileSeeker.generated.h"


/**
 * The Projectile's direction is set based on a local CombatTargetingComponent continually (i.e., on Tick).
 */
UCLASS(ClassGroup=(Projectile), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Projectile direction by continuously targetting a StatsComponent."))
class BATTLEENGINE_API UProjectileSeeker : public UProjectileDirectionTarget
{
	GENERATED_BODY()

public:

	UProjectileSeeker();

	virtual FVector GetDirection() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY()
	UCombatStatsComponent* TargetStats;
	
};
