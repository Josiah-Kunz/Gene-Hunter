#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "Engine/HitResult.h"
#include "ProjectileDamage.h"
#include "ProjectileMove.h"
#include "ProjectileDamageMultiple.generated.h"


UCLASS(Blueprintable, ClassGroup=(Projectile) , meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UProjectileDamageMultiple : public UProjectileDamage
{
	GENERATED_BODY()

public:
	
	/**
	 * Maximum number of times we can damage something. 
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	int32 NumDamageTimes = 1;

	/**
	 * If true, kill the Projectile Actor after we've damaged NumDamageTimes.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Projectile")
	bool KillAfterSpent = true;
	
	UProjectileDamageMultiple();

	virtual void InitializeProjectile(AActor* MoveCaster) override;
	
	virtual void OnProjectileCollision(const AActor* OtherActor, UCombatStatsComponent* EnemyStats) override;

private:

	/**
	 * To be set by the ProjectileMove when initialized. 
	 */
	UPROPERTY()
	UMoveData* MoveData;

	/**
	 * To be set by the ProjectileMove when initialized. 
	 */
	UPROPERTY()
	UCombatStatsComponent* CasterStats;

	/**
	 * Number of times this Projectile has damaged anything so far.
	 */
	UPROPERTY()
	int32 NumTimesDamaged = 0;
	
	/**
	 * On collision, we check this FIRST!
	 */
	UPROPERTY()
	bool bCanStillDamage = true;

	UPROPERTY()
	UProjectileMove* ProjectileMove;

};
