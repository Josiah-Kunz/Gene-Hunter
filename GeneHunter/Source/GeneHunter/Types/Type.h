

#pragma once

#include <iostream>
#include <fstream>
#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "../AttackModifier.h"
#include "FTypeArray1D.h"
#include "FTypeArray2D.h"
#include "Type.generated.h"

/*
 * Note: this is an interesting phenomenon also seen in statistical thermodynamics and has to do with a binomial
 *	expansion. MultiType has higher highs (hits select things much harder) and lower lows (is more easily resisted)
 *	compared to Coverage.
 */
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

#pragma region Constants
	
	inline static const FFloatRange EFFECTIVE = FFloatRange{
		FFloatRangeBound::Exclusive(1),
		FFloatRangeBound::Open()
	};
	inline static const FFloatRange INEFFECTIVE =  FFloatRange{
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
	 * Example: 
		* - TypesToAnalyze is the attack combinations {Fire, Water}
		* - AgainstTypes are all possible defenders combinations of length 2 (returned from GetAllTypeCombinations(Types, 2)).
		*	For example, {{Fire, Grass}, {Fire, Water}, {Grass, Water}, ...}
		* - Range = (1, INFINITY)
		* - bAtk = true (since TypesToAnalyze is attacking)
		* - Using Pokemon rules, the returns should be:
		*	- If multitype:
		*		- Ret[0].Array = {Steel, Normal}		(because Fire = 2x and Water = 1x)
		*		- Ret[1].Array = {Ground, Electric}		(because Fire = 1x and Water = 2x)
		*		- ...
		*	- If coverage:
		*		- Ret[0].Array = {Grass, Normal}		(because Fire alone would suffice)
		*		- Ret[1].Array = {Fire, Rock}			(because Water alone would suffice)
		*		- ...
	 */
	static TArray<FTypeArray1D*> Analyze(
			const TArray<UType*>& TypesToAnalyze,
			const TArray<FTypeArray1D*>& AgainstTypes,
			const FFloatRange Range,
			const EAttackModifierMode Mode = EAttackModifierMode::MultiType,
			const bool bAtk = true,
			const bool bDebug = false
			);

	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	static float GetNetModifier(const TArray<UType*>& AtkTypes, const TArray<UType*>& DefTypes,
		const EAttackModifierMode Mode = EAttackModifierMode::Coverage, const bool bDebug = false);

	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	static float GetNetModifier(const FTypeArray1D AtkTypes, const FTypeArray2D DefTypes,
		const EAttackModifierMode Mode = EAttackModifierMode::Coverage, const bool bDebug = false);
	
	/**
	 * Performs an analysis on the given Types.
	 *		- If bAnalyzeAtk, the "tested" Types are the attackers and the "untested" Types are the defenders.
	 *		- Ex: AnalyzeAll([all], 1, 1, [1, open), true) ==> all attacks that are 1v1 never resisted (e.g., Typeless would be in that result).
	 *
	 * The returned FTypeArray2D is broken into:
	 *	- Indices, e.g., Ret[0] for the data on the first attack combination
	 *	- Attacking combination, e.g., Ret[0].Array could yield {Fire, Water} as the attackers
	 *	- Defending combinations that fall within the given range, e.g., Ret[0].TypeArray2D could yield
	 *		{Grass, Normal,
	 *			Fire, Rock,
	 *			...}
	 *			(It's up to you to parse this array. In this example, do %2.)
	 */
	static void AnalyzeAll(TArray<UType*>& Types, const int NumTestedTypes, const int NumUntestedTypes,
		const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode, TArray<FTypeArray2D>& Result);


	/**
	 * Gets the net interaction between an attack (multi-Type or coverage; based on Mode) and a (multi-Type) defense.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void PrintStatistics(const int NumAttackers, const int NumDefenders, const FFloatRange Range,
		const EAttackModifierMode Mode, const bool bAtk, const bool bPrintToConsole, const bool bPrintToFile,
		UPARAM(ref) TArray<UType*>& Exclude);

#pragma endregion

#pragma region Getting Types

	/**
	 *	Deletes "None" entries in Type->AttackModifiers. This cannot be done by Blueprint methods (afaik).
	 */
	UFUNCTION(BlueprintCallable)
	static void PruneTypeAttackMods(UType* Type);

	/**
	 * Gets the Type Assets (not the Types themselves).
	 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetAllTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	/**
	 * Gets all Types.
	 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param Exclude A list of Types to exclude from this list.
	 * @param bSortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void GetAllTypes(TArray<UType*>& Types, UPARAM(ref) const TArray<UType*>& Exclude, const bool bSortABC = true);

public:

	/*
	 * Gets all Types.
	 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
	 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
	 */
	static void GetAllTypes(TArray<UType*>& Types, const bool bSortABC = true);

	/**
	 * Lazily gets all Type combinations. If you care about performance, take a look at how AnalyzeAll handles the problem.
	 * For example, for NumTypes = 2, this returns {A, B}, {A, C}, {A, D}, ...
	 */
	static TArray<FTypeArray1D*> GetAllTypeCombinations(const TArray<UType*>& Types, const int NumTypes);
	
#pragma endregion
	
private:
	
#pragma region Private functions

	/**
	 * A faster version for getting all types. For each "seed" given, if that seed has a non-zero list of AttackModifiers,
	 * this function will return the list's keys (Types).
	 */
    static TArray<UType*> GetAllTypesFromSeeds(TArray<UType*> TypesSeeds);

	static void InitializeModifier(float& Modifier, const EAttackModifierMode Mode);

	static bool IncrementIndices(const TArray<UType*>& Types, TArray<int>& Indices);

#pragma endregion


	
};
