#pragma once

#include "CoreMinimal.h"
#include "ProjectileDirection.h"
#include "ProjectileDirectionVector.generated.h"

/**
 * The Projectile's direction is set to the given FVector the first frame.
 */
UCLASS(ClassGroup=(Projectile), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Projectile direction by vector."))
class BATTLEENGINE_API UProjectileDirectionVector : public UProjectileDirection
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FVector Direction;

	virtual FVector GetDirection() override;
};
