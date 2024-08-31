#pragma once

#include "CoreMinimal.h"
#include "MoveData.h"
#include "ProjectileDependent.h"
#include "ProjectileDirection.h"
#include "Components/ActorComponent.h"

#include "ProjectileMove.generated.h"

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

#pragma endregion

protected:
	
	virtual void BeginPlay() override;

};
