#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "UObject/Object.h"
#include "Move.generated.h"

/**
 * Implements the static asset MoveData into something usable (e.g., with a cooldown). Collected by UMoveset.
 */
UCLASS()
class BATTLEENGINE_API UMove : public UObject
{
	GENERATED_BODY()

public:
	
	/**
	 * The owner who uses this Move must have CombatStats. Note: it is not the responsibility of this UObject to assign
	 * its own UCombatStatsComponent, but should be done elsewhere (e.g., in UMoveset).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	UCombatStatsComponent* Stats;

	/**
	 * The MoveData to keep track of. When the Move is executed, it calls functions from this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	UMoveData* MoveData;
	
	/**
	 * The time (in seconds) before this Move can be used again. This UMove itself can set the remaining cooldown, but
	 * doesn't tick, so it's up to another script (e.g., UMoveset) to keep track of when the Move can and cannot be
	 * used.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	float RemainingCD;

	/**
	 * Starts the MoveData by calling MoveData->SpawnObjects() and sets the RemainingCD appropriately.
	 *
	 * Does not check if RemainingCD should let this happen or not. That's up to another script (e.g., UMoveset).
	 */
	UFUNCTION(BlueprintCallable, Category="SpawnActor")
	void Execute();

	/**
	 * Calculates the cooldown based on MoveData and Stats and sets RemainingCD to this value.
	 */
	UFUNCTION(BlueprintCallable, Category="SpawnActor")
	void ResetCD();
	
};
