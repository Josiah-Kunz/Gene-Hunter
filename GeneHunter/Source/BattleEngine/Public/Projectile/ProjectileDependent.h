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

	virtual void InitializeComponent() override;

	virtual void InitializeProjectile();

};