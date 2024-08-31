#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionTarget.generated.h"

/**
 * The Projectile's direction is set to the given Actor. This only happens once (on creation) and never again.
 */
UCLASS(Blueprintable)
class BATTLEENGINE_API UProjectileDirectionTarget : public UProjectileDirection
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	AActor* Target;

	virtual FVector GetDirection() override;
};
