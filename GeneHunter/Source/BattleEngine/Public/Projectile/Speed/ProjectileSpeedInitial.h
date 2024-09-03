#pragma once

#include "CoreMinimal.h"
#include "ProjectileSpeed.h"
#include "ProjectileSpeedInitial.generated.h"

/**
 * Sets the Projectile's speed and max speed initially, but that's it.
 */
UCLASS(Blueprintable, ClassGroup=(Projectile) , meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UProjectileSpeedInitial : public UProjectileSpeed
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float InitialSpeed=100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	float MaxSpeed=100;
	
	UProjectileSpeedInitial();

	virtual void InitializeProjectile(AActor* MoveCaster) override;
	
};
