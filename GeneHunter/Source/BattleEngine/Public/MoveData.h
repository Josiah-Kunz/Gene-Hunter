#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "EffectToImplement.h"
#include "MoveCategory.h"
#include "MoveContact.h"
#include "SupportingText.h"
#include "Type.h"

#include "MoveData.generated.h"

/**
 * An asset that holds static data on a Move. Think of it as a Pokedex entry.
 */
UCLASS()
class BATTLEENGINE_API UMoveData : public UPrimaryDataAsset
{
	GENERATED_BODY()

#pragma region Variables

public:

	// Okay, not a variable, a constant =)
	inline static const FString DUMMY_IDENTIFIER = "Dummy";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	float BasePower;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	float BaseCooldown = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveCategory Category;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	EMoveContact Contact;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(Tooltip="If blank, this is the same as the asset name. Really only useful for special characters or a dynamic name."))
	FText DisplayName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(Tooltip="The effects to be inflicted on a collision."))
	TArray<FEffectToImplement> EffectsToImplement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data", meta=(EditCondition="bCanCategoryDoDamage()"))
	FFloatRange RandomRange = FFloatRange{0.85f, 1};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	FSupportingText SupportingText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Move Data")
	TArray<UType*> Types;

#pragma endregion

#pragma region Functions

public:

	/**
	 * Gets the MoveData Assets (not the UMoveData themselves). Includes both real and "dummy" MoveData.
	 * @param bSortABC If true, sorts alphabetically. Make false to improve performance.
	 * @param bIncludeDummy if true, include "dummy" MoveData (for unit testing only!).
	 * @param bIncludeReal if true, include "real" (in-game) MoveData. You always want this unless you're unit testing.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetAllMoveDataAssets(TArray<FAssetData>& MoveDataAssets, const bool bSortABC = false,
		const bool bIncludeDummy = false, const bool bIncludeReal = true);

	/**
	 * Gets all MoveData.
	 * @param MoveDataArray The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	static void GetAllMoveData(TArray<UMoveData*>& MoveDataArray, const bool bSortABC = true, const bool bDummyOnly = false);
	
	/**
	 * Gets all MoveData.
	 * @param MoveDataArray The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param Exclude A list of Types to exclude from this list.
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 * @param bDummyOnly If true, exclusively retrieves "dummy" MoveData (for unit testing). If false, exclusively retrieves real, in-game MoveData.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void GetAllMoveData(TArray<UMoveData*>& MoveDataArray, UPARAM(ref) const TArray<UMoveData*>& Exclude,
		const bool bSortABC = true, const bool bDummyOnly = false);

	UFUNCTION(BlueprintCallable)
	static UMoveData* GetMoveDataByName(UPARAM(ref) const TArray<UMoveData*>& Pool, const FName Name);
	
protected:
	
	bool bCanCategoryDoDamage() const
	{
		return Category == EMoveCategory::PhysicalDamage || 
			   Category == EMoveCategory::SpecialDamage || 
			   Category == EMoveCategory::SpecialHealing;
	}

#pragma endregion
	
};
