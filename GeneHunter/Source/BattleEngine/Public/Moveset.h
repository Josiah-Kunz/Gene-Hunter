#pragma once

#include "CoreMinimal.h"
#include "EffectableComponent.h"
#include "Move.h"

#include "Moveset.generated.h"

/**
 * A class to hold and manage Moves.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UMoveset : public UEffectableComponent
{
	GENERATED_BODY()

#pragma region Variables

private:

	UPROPERTY()
	TArray<UMove*> Moves;

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
	 * @return The current Moves known in this set. The set returned is not alterable. To alter the Moves in the set,
	 * use the appropriate setter functions.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	const TArray<UMove*> GetMoves() const;

	/**
	 * Sets new Moves.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	void SetMoves(const TArray<UMove*> NewMoves);

	/**
	 * 
	 * @param Index Position of the new Move (starting at zero).
	 * @param NewMove New Move to set. Will override the old move at Index (if any).
	 * @return true if the new Move was successfully set.
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool SetMoveByIndex(const uint8 Index, UMove* NewMove);

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
	bool UseExistingMove(const UMove* Move);

	/**
	 * 
	 * @param Index 
	 * @return true if the Index > 0 and Index <= NumMoves().
	 */
	UFUNCTION(BlueprintCallable, Category="Moveset")
	bool IsValidIndex(const uint8 Index) const;

};

#pragma endregion