#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "ProjectileDependent.h"
#include "ProjectileDamage.generated.h"

/**
 * How the Projectile deals damage (or healing, or doesn't deal damage, or whatever). Could be single damage, damage N
 * times, damage while collided, etc.
 *
 * OnProjectileCollision gets called via BP_Projectile_Move (Blueprint), then UProjectileMove (script), then this. 
 * 
 * By default, this script does nothing.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UProjectileDamage : public UProjectileDependent
{
	GENERATED_BODY()

public:
	
	/**
	 * Possible Actors to spawn when the Move hits.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	TArray<TSubclassOf<UActorSpawnScheme>> SpawnOnHit;
	
	// Sets default values for this component's properties
	UProjectileDamage();

	virtual void InitializeProjectile(AActor* MoveCaster) override;

	virtual void OnProjectileCollision(const AActor* OtherActor, UCombatStatsComponent* EnemyStats);

};
