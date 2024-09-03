#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionNone.generated.h"

/**
 * The Projectile has a zero direction. This causes the Projectile to have zero velocity on creation.
 */
UCLASS()
class BATTLEENGINE_API UProjectileDirectionNone : public UProjectileDirection
{
	GENERATED_BODY()

public:

	virtual FVector GetDirection() override;
};
