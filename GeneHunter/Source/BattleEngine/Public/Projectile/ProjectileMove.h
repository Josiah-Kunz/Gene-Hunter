#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "MoveData.h"
#include "ProjectileDamage.h"
#include "ProjectileDependent.h"
#include "ProjectileDirection.h"
#include "Components/ActorComponent.h"
#include "ProjectileSpeed.h"

#include "ProjectileMove.generated.h"

// Delegates
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProjectileEnd);

/**
 * A class to marry MoveData to a Projectile.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UProjectileMove : public UProjectileDependent
{
	GENERATED_BODY()

#pragma region Variables

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UMoveData* MoveData;

	/**
	 * This controls the direction of the Projectile.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileDirection* Direction;
	
	/**
	 * This controls the speed of the Projectile.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileSpeed* Speed;
	
	/**
	 * How the Projectile handles dealing damage.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileDamage* Damage;

	/**
	 * Called just before the Projectile is deleted.
	 */
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnProjectileEnd OnProjectileEnd;

private:

	UPROPERTY()
	bool bInitialized;

#pragma endregion
public:

	virtual void InitializeProjectile(AActor* MoveCaster) override;

	UFUNCTION(BlueprintCallable)
	virtual void OnProjectileCollision(const AActor* OtherActor, UCombatStatsComponent* EnemyStats);

	UFUNCTION(BlueprintCallable)
	virtual void EndProjectile();

};
