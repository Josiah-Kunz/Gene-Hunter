#pragma once

#include "CoreMinimal.h"
#include "EffectableComponent.h"
#include "MoveInstance.h"

#include "Moveset.generated.h"

/**
 * A class to hold and manage Moves.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UMoveset : public UEffectableComponent
{
	GENERATED_BODY()

#pragma region Variables

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Moveset")
	TArray<FMoveInstance> Moves;

#pragma endregion

#pragma region Functions

public:
	
	/**
	 * Ensures we cannot tick.
	 */
	UMoveset();

	/**
	 * 
	 * @return The maximum number of moves in the Moveset.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	uint8 MaxMoves() const;

	/**
	 * 
	 * @param Index Position of the new Move (starting at zero).
	 * @param NewMove New Move to set. Will override the old move at Index (if any).
	 * @return true if the new Move was successfully set.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool SetMoveByIndex(const uint8 Index, FMoveInstance& NewMove);

	/**
	 * Executes the Move at the given index.
	 * @param Index Use the Move at this position. Starts at zero.
	 * @return true if the Move was non-null and used.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool UseMoveByIndex(const uint8 Index);

	/**
	 * Executes the given Move (that's part of the moveset).
	 * @param Move The Move to use. This must be part of the moveset.
	 * @return false if the Move was null or not part of the moveset.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool UseExistingMove(const FMoveInstance& Move);

	/**
	 * 
	 * @param Index 
	 * @return true if the Index > 0 and Index <= NumMoves().
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool IsValidIndex(const uint8 Index) const;

	UFUNCTION(BlueprintCallable, Category="Moveset")
	void SetCombatStats(UCombatStatsComponent* CombatStats);

protected:
	
	/**
	 * Ensures our array only has MaxMoves (4 by default) entries.
	 */
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;

private:

	void ValidateMoves();

};

#pragma endregion