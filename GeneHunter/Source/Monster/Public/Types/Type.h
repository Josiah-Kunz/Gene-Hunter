

#pragma once

#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackModifier.h"
#include "AttackModifierMode.h"
#include <algorithm>
#include "UI/Public/SupportingText.h"
#include "BPLibraries/Public/AssetFunctionLibrary.h"
#include "Type.generated.h"

/**
 * Like Types in Pokemon, this class is the building block for a system of advantages and disadvantages in combat. Types may be assigned to Monsters or Moves.
 */
UCLASS()
class MONSTER_API UType : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:

#pragma region Constants
	
	inline static const FFloatRange Effective = FFloatRange{
		FFloatRangeBound::Exclusive(1),
		FFloatRangeBound::Open()
	};
	inline static const FFloatRange Ineffective =  FFloatRange{
		FFloatRangeBound::Open(),
		FFloatRangeBound::Exclusive(1)
	};
	
#pragma endregion

#pragma region Variables
	
	/**
	 * A map of modifiers that this Type gets when attacking other Types.
	 **/
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TMap<UType*, FAttackModifier> AttackModifiers;

	/**
	 * An array of LinearColors associated with this Type to do with as you please. For example, the zeroth color can be associated with a background color.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FLinearColor> Colors;

	/**
	 * The Text that describes this Type (e.g., dev note, flavor text, etc.).
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FSupportingText SupportingText;

#pragma endregion

#pragma region Public functions
	
	/**
	 * Gets the net modifier when using default rules for combining modifiers. Explicitly:
	 *
	 * Multi-Type
	 * ----------
	 *	- (-1 & 2)	 ==> (-1/2)
	 *	- (-1 & 1)	 ==> (-1)
	 *	- (-1 & 1/2) ==> (-1)
	 *	- (-1 & 0)	 ==> (-1)
	 *	- (-1 & -1)	 ==> (-1)
	 *
	 *	- (0 & 1)	 ==> (0)
	 *	- (2 & 1/2)	 ==> (1)
	 *
	 * Coverage
	 * --------
	 *	- (-1 & 2)	 ==> 2
	 *	- (-1 & 1)	 ==> 1
	 *	- (-1 & 1/2) ==> 1/2
	 *	- (-1 & 0)	 ==> 0
	 *	- (-1 & -1)	 ==> -1
	 *
	 *	- (0 & 1)	 ==> 1
	 *	- (2 & 1/2)	 ==> 2
	 */
	UFUNCTION(BlueprintCallable)
	static float CombineModifiers(const float A, const float B,
		const EAttackModifierMode Mode = EAttackModifierMode::MultiType);

	/**
	 * Gets the attack modifier when this Type attacks the given Type. If the attack
	 * modifier is not defined, returns 1.
	 * This is much safer than Type->AttackModifiers[AgainstType].Modifier.
	 */
	UFUNCTION(BlueprintCallable)
	float GetAttackModifier(const UType* AgainstType);
	
	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	static float GetNetModifier(const TArray<UType*>& AtkTypes, const TArray<UType*>& DefTypes,
		const EAttackModifierMode Mode = EAttackModifierMode::Coverage, const bool bDebug = false);

	/**
	 * Sets the modifier to a starting value based on Mode:
	 *	- MultiType: Modifier = 1
	 *	- Coverage: Modifier = -INFINITY
	 *	- Else: error
	 */
	static void InitializeModifier(float& Modifier, const EAttackModifierMode Mode);

	/**
	 *	Deletes "None" entries in Type->AttackModifiers. This cannot be done by Blueprint methods (afaik).
	 */
	UFUNCTION(BlueprintCallable)
	static void PruneTypeAttackMods(UType* Type);
	
#pragma endregion

#pragma region Getting Types

	/**
	 * Gets the Type Assets (not the Types themselves).
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetAllTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	/**
	 * Gets all Types.
	 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	static void GetAllTypes(TArray<UType*>& Types, const bool bSortABC = true);
	
	/**
	 * Gets all Types.
	 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param Exclude A list of Types to exclude from this list.
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void GetAllTypes(TArray<UType*>& Types, UPARAM(ref) const TArray<UType*>& Exclude, const bool bSortABC = true);

	/**
	 * Parses through this Type's AttackModifiers and returns the defenders who are within the specified range.
	 */
	UFUNCTION(BlueprintCallable)
	void GetTypesInRange(UPARAM(ref) const TArray<UType*>& AllTypes, const FFloatRange Range,
	                     TArray<UType*>& Defenders);

	/**
	 * Parses through AllTypes to find attackers whose AttackModifiers are within the specified range when attacking this Type.
	 */
	UFUNCTION(BlueprintCallable)
	void GetTypesInRangeDefending(UPARAM(ref) const TArray<UType*>& AllTypes, const FFloatRange Range,
	                              TArray<UType*>& Attackers);
	
#pragma endregion

#pragma region Utilities
	
	/*
	 * Note: these are mostly used in unit tests.
	 */

	/**
	 * Tests if the arrays of Type* and Type* are equal (by name).
	 */
	static bool ArraysAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected,
		FString& Description);

	/**
	 * Returns, e.g., "[Air, Earth, Fire, Water]".
	 */
	static FString ArrayToFString(const TArray<UType*>& Array);
	
	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<UType*>& Container, const UType* SearchTarget,
		const bool bByName = true);

#pragma endregion
	
private:
	
#pragma region Private functions

	/**
	 * A faster version for getting all types. For each "seed" given, if that seed has a non-zero list of AttackModifiers,
	 * this function will return the list's keys (Types).
	 */
    static TArray<UType*> GetAllTypesFromSeeds(TArray<UType*> TypesSeeds);


#pragma endregion
	
};
