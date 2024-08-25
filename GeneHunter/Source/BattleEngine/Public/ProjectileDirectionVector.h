#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionVector.generated.h"

/**
 * The Projectile's direction is set to the given FVector.
 */
UCLASS(Blueprintable)
class BATTLEENGINE_API UProjectileDirectionVector : public UProjectileDirection
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector Direction;

	virtual FVector GetTargetDirection() override;
};
