

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../AttackModifier.h"
#include "FTypeArray1.h"
#include "FTypeArray2.h"
#include "Type.generated.h"

UENUM(BlueprintType)
enum class EAttackModifierMode : uint8
{
	MultiType		UMETA(DisplayName = "Multi-Type", Tooltip="Takes the Types in the array as a single, multi-Typed attack."),
	Coverage		UMETA(DisplayName = "Coverage", Tooltip="Takes the Types in the array as separate, singly-Typed attacks."),
};

/**
 * Like Types in Pokemon, this class is the building block for a system of advantages and disadvantages in combat. Types may be assigned to Monsters or Moves.
 */
UCLASS()
class GENEHUNTER_API UType : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	
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
	 * Gets the net modifier when using default rules for combining modifiers. For example:
	 * 
	 *	- (-1 & 2)	 ==> (-1/2)
	 *	- (-1 & 1)	 ==> (-1)
	 *	- (-1 & 1/2) ==> (-1)
	 *	- (-1 & 0)	 ==> (-1)
	 *	- (-1 & -1)	 ==> (-1)
	 *
	 *	- (0 & 1)	 ==> (0)
	 *	- (2 & 1/2)	 ==> (1)
	 */
	UFUNCTION(BlueprintCallable)
	static float CombineModifiers(const float A, const float B);

	/**
	 * Gets Types whose defense modifiers are between Min and Max when attacked by the given AtkTypes.
	 * For example, a range of (1, INFINITY) gets Types who are "bad against" these AtkTypes (since they receive more damage).
	 * Pokemon example:
	 *		- AnalyzeAtk({Flying, Ground}, 1, INFINITY, false, MultiType) ==> {Fire, Poison, Fighting}
	 *		- AnalyzeAtk({Flying, Ground}, 1, INFINITY, false, Coverage) ==> {Electric, Fire, Poison, Rock, Steel, B.ug, Fighting, Grass}
	 * @param TypesToAnalyze The Types doing the attacking.
	 * @param Range If the modifier is in the given range, the matchup is "successful".
	 * @param Mode Determines whether the analysis is being done for a single multi-Typed attack or for coverage of several attacks.
	 * @param bAtk True if doing the analysis on attacking Types, false if on defending Types.
	 */
	/*
	UFUNCTION(BlueprintCallable)
	static TArray<UType*> AnalyzeVsSingle(
			const TArray<UType*> TypesToAnalyze,
			const FFloatRange Range,
			const EAttackModifierMode Mode = EAttackModifierMode::MultiType,
			const bool bAtk = true
			);*/

	/**
	 * Example: 
		* - TypesToAnalyze is the attack combinations {Fire, Water}
		* - AgainstTypes are all possible defenders combinations of length 2 (returned from GetAllTypeCombinations(Types, 2))
		* - Range = (1, INFINITY)
		* - bAtk = true (since TypesToAnalyze is attacking)
		* - Using Pokemon rules, the returns should be:
		*	- If multitype:
		*		- Ret[0].TypeArray = {Steel, Normal}		(because Fire = 2x and Water = 1x)
		*		- Ret[1].TypeArray = {Ground, Electric}		(because Fire = 1x and Water = 2x)
		*		- ...
		*	- If coverage:
		*		- Ret[0].TypeArray = {Grass, Normal}		(because Fire alone would suffice)
		*		- Ret[1].TypeArray = {Fire, Rock}			(because Water alone would suffice)
		*		- ...
	 */
	static TArray<FTypeArray1*> Analyze(
			const TArray<UType*>& TypesToAnalyze,
			const TArray<FTypeArray1*>& AgainstTypes,
			const FFloatRange Range,
			const EAttackModifierMode Mode = EAttackModifierMode::MultiType,
			const bool bAtk = true,
			const bool bDebug = false
			);

	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	UFUNCTION(BlueprintCallable)
	static float GetNetModifier(const TArray<UType*>& AtkTypes, const TArray<UType*>& DefTypes,
		const EAttackModifierMode Mode = EAttackModifierMode::Coverage);
	
	/**
	 * Performs an analysis on the given Types.
	 *		- If AnalyzeAtk, the "tested" Types are the attackers and the "untested" Types are the defenders.
	 *		- Ex: AnalyzeAll([all], 1, 1, [1, open), true) ==> all attacks that are 1v1 never resisted (e.g., Typeless would be in that result).
	 */
	UFUNCTION(BlueprintCallable)
	static TArray<UType*> AnalyzeAll(TArray<UType*> Types, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode);

#pragma endregion

#pragma region Sorting for debug purposes

	/**
	 * Sorts the given Types by the number of AttackModifiers within the specified range.
	 * For example, if Water is only good attacking against Fire, it would be near the end of the list.
	 * The returned FTypeArray2 is broken into:
	 *	- Indices, e.g., Sorted[0] for the data on the first attack combination
	 *	- Attacking combination, e.g., Sorted[0].TypeArray could yield {Fire, Water} as the attackers
	 *	- Defending combinations that fall within the given range, e.g., Sorted[0].TypeArray2 could yield
	 *		{Grass, Normal,
	 *			Fire, Rock,
	 *			...}
	 *			(It's up to you to parse this array. In this example, do %2.)
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesAttacking(const TArray<UType*> Types, const int NumAtkTypes, const int NumDefTypes,
		const FFloatRange Range, const EAttackModifierMode Mode, TArray<FTypeArray2>& Sorted);

	/**
	 * Sorts the given Types by the number of defensible Types within the specified range.
	 * For example, if Fire is only weak (defending) to Water, it would be near the end of the list.
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const FFloatRange Range);

	/**
	 * Sorts the given Types by the ratio of [effective:ineffective] attack modifiers from high ratio to low ratio.
	 * For example, if Fire is effective against Nature and resisted against Water, it would be a 1:1 ratio (and hence near the middle of the list).
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesAttackingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted);

	/**
	 * Sorts the given Types by the ratio of [resists:weak to] from high ratio to low ratio.
	 * For example, if Nature resists Water and is weak to Fire, it would be a 1:1 ratio (and hence near the middle of the list).
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesDefendingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted);

	/**
	 * Gets all combinations of attackers who have neutral coverage.
	 * For example, in Pokemon, if NumTypes=2, Ice/Electric would be in the returned array.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetCoverage(const TArray<UType*> Types, TArray<UType*>& Coverage, const int NumAtkTypes=2, const int NumDefTypes=2);

	/**
	 * Lazily gets all Type combinations. If you care about performance, take a look at how AnalyzeAll handles the problem.
	 * For example, for NumTypes = 2, this returns {A, B}, {A, C}, {A, D}, ...
	 */
	static TArray<FTypeArray1*> GetAllTypeCombinations(const TArray<UType*>& Types, const int NumTypes);

private:
	static bool IncrementIndices(const TArray<UType*> Types, TArray<int>& Indices);
	
#pragma endregion

#pragma region Getting Types
	
	UFUNCTION(BlueprintCallable)
	static void PruneTypeAttackMods(UType* Type);

	UFUNCTION(BlueprintCallable)
	static void GetAllTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void GetAllTypes(TArray<UType*>& Types, const TArray<UType*> Exclude, const bool bSortABC = true);

public:
	static void GetAllTypes(TArray<UType*>& Types, const bool bSortABC = true);
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
