#pragma once

#include "CoreMinimal.h"
#include "ProjectileDamage.h"
#include "ProjectileDamageNone.generated.h"


UCLASS(Blueprintable, ClassGroup=(Projectile) , meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UProjectileDamageNone : public UProjectileDamage
{
	GENERATED_BODY()

public:

	UProjectileDamageNone();
};
