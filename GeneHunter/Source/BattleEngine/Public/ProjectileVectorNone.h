#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirection.h"
#include "ProjectileVectorNone.generated.h"

/**
 * The Projectile has a zero direction. This causes the Projectile to have zero velocity on creation.
 */
UCLASS(Blueprintable)
class BATTLEENGINE_API UProjectileVectorNone : public UProjectileDirection
{
	GENERATED_BODY()

public:

	virtual FVector GetTargetDirection() override;
};
