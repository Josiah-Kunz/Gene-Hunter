#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ProjectileDirection.generated.h"

UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UProjectileDirection : public UObject
{
	GENERATED_BODY()

public:
	UProjectileDirection();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	virtual FVector GetTargetDirection() PURE_VIRTUAL(UProjectileTarget::GetTargetDirection, return FVector::ZeroVector;);
};
