#pragma once

#include "CoreMinimal.h"
#include "EffectToImplement.h"
#include "MoveCategory.h"
#include "MoveContact.h"
#include "ActorSpawnScheme.h"
#include "MoveUsabilityScheme.h"
#include "SupportingText.h"
#include "Type.h"

#include "MoveData.generated.h"

/**
 * An asset that holds static data on a Move. Think of it as a Pokédex entry.
 */
UCLASS()
class BATTLEENGINE_API UMoveData : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Variables

public:

	// Okay, not a variable, a constant =)
	inline static const FString DUMMY_IDENTIFIER = "Dummy";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData", meta=(EditCondition="bCanDoDamage"))
	float BasePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	float BaseCooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	EMoveCategory Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	EMoveContact Contact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData",
		meta=(Tooltip="If blank, this is the same as the asset name. Really only useful for special characters or a dynamic name."))
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData",
		meta=(Tooltip="The effects to be inflicted on a collision."))
	TArray<FEffectToImplement> EffectsToImplement;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData",
		meta=(Tooltip="If true, only up to one Effect in EffectsToImplement may be attached. If false, each Effect's probability is checked individually, resulting in (possibly) multiple Effects being attached."))
	bool bMutualEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData", meta=(EditCondition="bCanDoDamage"))
	FFloatRange RandomRange = FFloatRange{0.85f, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	FSupportingText SupportingText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	TArray<UType*> Types;

	/**
	 * Possible Actors and how they spawn when the Move is cast.
	 * For example, maybe this MoveData spawns 2--4 bees to attack your enemy.
	 * You can create your own class that inherits from UActorSpawnScheme* to customize spawning. For example:
	 *	- Position (spawn 1 bee right on top of the enemy and 2 bees close to me)
	 *	- Conditions (if <50% health, spawn more bees)
	 *	- And so forth
	 * If you want to spawn something when the Move hits or expires, do it in the Projectile (e.g., ProjectileDamage.h).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	TArray<TSubclassOf<UActorSpawnScheme>> SpawnOnCast;
	
	/**
	 * If null, the Move can be used all the time (but still respects cooldowns).
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="MoveData")
	TSubclassOf<UMoveUsabilityScheme> UsabilityScheme;

private:
	
	UPROPERTY()
	bool bCanDoDamage;
	
#pragma endregion

#pragma region Functions

public:

	UMoveData();

	/**
	 * Gets the MoveData Assets (not the UMoveData themselves). Includes both real and "dummy" MoveData.
	 * @param MoveDataAssets Set this to empty or I will!
	 * @param bSortABC If true, sorts alphabetically. Make false to improve performance.
	 * @param bIncludeDummy if true, include "dummy" MoveData (for unit testing only!).
	 * @param bIncludeReal if true, include "real" (in-game) MoveData. You always want this unless you're unit testing.
	 */
	UFUNCTION(BlueprintCallable, Category="MoveData")
	static void GetAllMoveDataAssets(TArray<FAssetData>& MoveDataAssets, const bool bSortABC = false,
		const bool bIncludeDummy = false, const bool bIncludeReal = true);

	/**
	 * Gets all MoveData.
	 * @param MoveDataArray The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 * @param bDummyOnly If true, gets the "dummy" MoveData that should only be used in unit tests (not in-game).
	 */
	static void GetAllMoveData(TArray<UMoveData*>& MoveDataArray, const bool bSortABC = true, const bool bDummyOnly = false);
	
	/**
	 * Gets all MoveData.
	 * @param MoveDataArray The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param Exclude A list of Types to exclude from this list.
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 * @param bDummyOnly If true, exclusively retrieves "dummy" MoveData (for unit testing). If false, exclusively retrieves real, in-game MoveData.
	 */
	UFUNCTION(BlueprintCallable, Category="MoveData", meta = (AutoCreateRefTerm = "Exclude"))
	static void GetAllMoveData(TArray<UMoveData*>& MoveDataArray, UPARAM(ref) const TArray<UMoveData*>& Exclude,
		const bool bSortABC = true, const bool bDummyOnly = false);

	UFUNCTION(BlueprintCallable, Category="MoveData")
	static UMoveData* GetMoveDataByName(UPARAM(ref) const TArray<UMoveData*>& Pool, const FName Name);

	/**
	 * Gets the name that should be displayed in-game. If DisplayName is blank, returns the asset name.
	 */
	UFUNCTION(BlueprintCallable, Category="MoveData")
	FText GetDisplayName();
	
protected:

#if WITH_EDITOR

	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	
#endif

private:

	void SetCanDoDamage();
	
#pragma endregion
	
};
