

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackModifier.h"
#include "Type.generated.h"

UENUM(BlueprintType)
enum class ModifierFetchMode : uint8
{
	Default			UMETA(DisplayName = "Default", Tooltip="Pokemon rules, except with healing:\n" + " (-1 & 2)   = -0.5\n" + " (-1 & 1)   = -1\n" + " (-1 & 0.5) = -1\n" + " (-1 & 0)   = -1\n" + " (-1 & -1/2)  = -1"),
	Multiplicative	UMETA(DisplayName = "Multiplicative"),
	Additive		UMETA(DisplayName = "Additive"),
	Min				UMETA(DisplayName="Min"),
	Max				UMETA(DisplayName="Max"),
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
	 * Gets the net modifier when an attack of the given Type(s) damages the other Type(s).
	 * For example, if a Toxic+Fire attack attempts to damage a Metal Type, this function will return zero if 
	 * multiplicative (Metal is immune to Toxic, so 0*2=0) or 2 if max.
	 */
	UFUNCTION(BlueprintCallable)
	static float GetNetModifier(const TArray<UType*> AttackingTypes, const TArray<UType*> DefendingTypes, const ModifierFetchMode FetchMode = ModifierFetchMode::Default);

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
	
#pragma region Attacking type effectiveness
	
	/*
	 * Gets Types that take increased damage from this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetEffectiveAgainstTypes() const;

	/*
	 * Gets Types that take decreased damage from this Type (not including immune or healed).
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetIneffectiveAgainstTypes() const;

	/*
	 * Gets Types that are immune to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetZeroDamageToTypes() const;

	/*
	 * Gets Types that are healed instead of damaged when this Type attacks.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetHealsTypes() const;

	/*
	 * Gets Types that are damaged normally by this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetNeutralAttackTypes() const;

	/*
	 * Gets Types whose damage modifiers defending this Type are between Min and Max.
	 * For example, a range of (1, INFINITY) gets Types who are "weak to" this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetAttackingTypesBetween(const float Min, const float Max, const bool Inclusive = true) const;

	/*
	 * Gets Types whose combined defending modifiers are between Min and Max for the given attacking Types.
	 * For example, a range of (1, INFINITY) gets Types who are "weak to" the given multi-Type attack.
	 * Pokemon example:
	 *		GetMultiAtkTypes({Ground, Flying}, {[ALL]}, 1, INFINITY)  --> {Fighting, Fire, Poison}
	 *		GetMultiAtkTypes({Ground, Flying}, {[ALL]}, -INFINITY, 1) --> {Flying}
	 *		
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "DefTypes"))
	static TArray<UType*> GetMultiAtkTypes(const TArray<UType*> AtkTypes, TArray<UType*> DefTypes, const float Min, const float Max, const bool Inclusive = true);

#pragma endregion

#pragma region Defending type effectiveness

	/*
	 *	Gets Types who deal extra damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetWeakToTypes() const;

	/*
	 *	Gets Types who deal reduced damage to this Type, not counting zero (immune) or negative (healed by) modifiers.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetResistsTypes() const;

	/*
	 *	Gets Types who heal this Type instead of hurting it when attacking.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetHealedByTypes() const;

	/*
	 *	Gets Types who deal neutral damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetNeutralDefendTypes() const;

	/*
	 *	Gets Types who deal zero damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetImmuneToTypes() const;
	
	/*
	 * Gets Types whose damage modifiers are between Min and Max when attacking this Type.
	 * For example, a range of (1, INFINITY) gets Types who are "good against" this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetDefendingTypesBetween(const float Min, const float Max, const bool Inclusive = true) const;

#pragma endregion

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
