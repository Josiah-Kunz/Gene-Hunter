#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "ProjectileDependent.generated.h"

/**
 * A base class for ActorComponents that are required by a Projectile. Has:
 *
 *	- A UProjectileMovementComponent property that is automatically sought when the component is added.
 *	- An InitializeProjectile function that is overridable. This is called by ProjectileMove on BeginPlay. This is
 *		useful for, e.g., setting the projectile's direction on the first frame.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UProjectileDependent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	UProjectileMovementComponent* Projectile;

	/**
	 * The one who uses the Move (that in turn spawns the Projectile).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	AActor* Caster;

	/**
	 * Called automatically when the component is first activated on an Actor.
	 */
	virtual void InitializeComponent() override;

	/**
	 * Called manually when initialized.
	 */
	UFUNCTION(Blueprintable)
	virtual void InitializeProjectile(AActor* MoveCaster);

	UFUNCTION(Blueprintable)
	virtual void Enable();

	UFUNCTION(Blueprintable)
	virtual void Disable();

};