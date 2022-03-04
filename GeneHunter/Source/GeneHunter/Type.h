

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackModifier.h"
#include "Type.generated.h"

UENUM(BlueprintType)
enum class EAttackModifierMode : uint8
{
	MultiType		UMETA(DisplayName = "Multi-Type", Tooltip="Takes the Types in the array as a single, multi-Typed attack."),
	Coverage		UMETA(DisplayName = "Coverage", Tooltip="Takes the Types in the array as separate, singly-Typed attacks."),
};

/**
 * 
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

	/*
	 * An array of LinearColors associated with this Type to do with as you please. For example, the zeroth color can be associated with a background color.
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FLinearColor> Colors;

	/*
	 * The Text that describes this Type (e.g., dev note, flavor text, etc.).
	 */
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FSupportingText SupportingText;

#pragma endregion

	/*
	 * Gets the net modifier when using default rules for combining modifiers. For example:
	 * 
	 *	(-1 & 2)	-> (-1/2)
	 *	(-1 & 1)	-> (-1)
	 *	(-1 & 1/2)	-> (-1)
	 *	(-1 & 0)	-> (-1)
	 *	(-1 & -1)	-> (-1)
	 *
	 *	(0 & 1)		-> (0)
	 *	(2 & 1/2)	-> (1)
	 */
	UFUNCTION(BlueprintCallable)
	static float CombineModifiers(const float A, const float B);

	/*
	 * Gets Types whose defense modifiers are between Min and Max when attacked by the given AtkTypes.
	 * For example, a range of (1, INFINITY) gets Types who are "bad against" these AtkTypes (since they receive more damage).
	 * Pokemon example:
	 *		- AnalyzeAtk({Flying, Ground}, 1, INFINITY, false, MultiType) ==> {Fire, Poison, Fighting}
	 *		- AnalyzeAtk({Flying, Ground}, 1, INFINITY, false, Coverage) ==> {Electric, Fire, Poison, Rock, Steel, B.ug, Fighting, Grass}
	 * @param AtkTypes The Types doing the attacking.
	 * @param Min The minimum AttackModifier to consider.
	 * @param Max The maximum AttackModifier to consider.
	 * @param Inclusive If true, include results that are Min <= result <= Max.
	 * @param Mode Determines whether the analysis is being done for a single multi-Typed attack or for coverage of several attacks.
	 */
	 UFUNCTION(BlueprintCallable)
	static TArray<UType*> Analyze(
			const TArray<UType*> TypesToAnalyze,
			const FFloatRange Range,
			const EAttackModifierMode Mode = EAttackModifierMode::MultiType,
			const bool bAtk = true
			);

	
	UFUNCTION(BlueprintCallable)
	static TArray<UType*> AnalyzeAtk(
		const TArray<UType*> AtkTypes,
		const FFloatRange Range,
		const EAttackModifierMode Mode = EAttackModifierMode::MultiType);

	UFUNCTION(BlueprintCallable)
	static TArray<UType*> AnalyzeDef(
		const TArray<UType*> DefTypes,
		const FFloatRange Range,
		const EAttackModifierMode Mode = EAttackModifierMode::MultiType);

	/*
	 * Gets the net interaction between a (multi-Type) attack and a (multi-Type) defense.
	 */
	UFUNCTION(BlueprintCallable)
	static float GetNetModifier(const TArray<UType*> AtkTypes, const TArray<UType*> DefTypes);
	
	/*
	 * Performs an analysis on the given Types.
	 *		- If AnalyzeAtk, the "tested" Types are the attackers and the "untested" Types are the defenders.
	 *		- Ex: AnalyzeAll([all], 1, 1, [1, open), true) ==> all attacks that are 1v1 never resisted (e.g., Typeless would be in that result).
	 */
	UFUNCTION(BlueprintCallable)
	static TArray<UType*> AnalyzeAll(TArray<UType*> Types, const int NumTestedTypes, const int NumUntestedTypes, const FFloatRange Range, const bool bAnalyzeAtk);

private:
    static TArray<UType*> GetAllTypes(TArray<UType*> TypesSeeds);

#pragma region Sorting for debug purposes

	/*
	 * Sorts the given Types by the number of AttackModifiers within the specified range.
	 * For example, if Water is only good attacking against Fire, it would be near the end of the list.
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesAttacking(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive);

	/*
	 * Sorts the given Types by the number of defensible Types within the specified range.
	 * For example, if Fire is only weak (defending) to Water, it would be near the end of the list.
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive);

	/*
	 * Sorts the given Types by the ratio of [effective:ineffective] attack modifiers from high ratio to low ratio.
	 * For example, if Fire is effective against Nature and resisted against Water, it would be a 1:1 ratio (and hence near the middle of the list).
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesAttackingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted);

	/*
	 * Sorts the given Types by the ratio of [resists:weak to] from high ratio to low ratio.
	 * For example, if Nature resists Water and is weak to Fire, it would be a 1:1 ratio (and hence near the middle of the list).
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesDefendingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted);

	/*
	 * Gets all combinations of attackers who have neutral coverage.
	 * For example, in Pokemon, if NumTypes=2, Ice/Electric would be in the returned array.
	 */
	UFUNCTION(BlueprintCallable)
	static void GetCoverage(const TArray<UType*> Types, TArray<UType*>& Coverage, const int NumAtkTypes=2, const int NumDefTypes=2);

private:
	static bool IncrementIndices(const TArray<UType*> Types, TArray<int>& Indices);
	
#pragma endregion
	
};
