

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "AttackModifier.h"
#include "Type.generated.h"

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
	
#pragma region Attacking type effectiveness
	
	/*
	 * Gets Types that take increased damage from this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetEffectiveAgainstTypes();

	/*
	 * Gets Types that take decreased damage from this Type (not including immune or healed).
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetIneffectiveAgainstTypes();

	/*
	 * Gets Types that are immune to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetZeroDamageToTypes();

	/*
	 * Gets Types that are healed instead of damaged when this Type attacks.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetHealsTypes();

	/*
	 * Gets Types that are damaged normally by this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetNeutralAttackTypes();

	/*
	 * Gets Types whose damage modifiers defending this Type are between Min and Max.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetAttackingTypesBetween(const float Min, const float Max, const bool Inclusive = true);

	
	
	/*
	 * Sorts the given Types by the number of AttackModifiers within the specified range. For example, if Water is only good attacking against Fire, it would be near the end of the list.
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesAttacking(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive);

#pragma endregion

#pragma region Defending type effectiveness

	/*
	 *	Gets Types who deal extra damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetWeakToTypes();

	/*
	 *	Gets Types who deal reduced damage to this Type, not counting zero (immune) or negative (healed by) modifiers.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetResistsTypes();

	/*
	 *	Gets Types who heal this Type instead of hurting it when attacking.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetHealedByTypes();

	/*
	 *	Gets Types who deal neutral damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetNeutralDefendTypes();

	/*
	 *	Gets Types who deal zero damage to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetImmuneToTypes();
	
	/*
	 * Gets Types whose damage modifiers are between Min and Max when attacking this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetDefendingTypesBetween(const float Min, const float Max, const bool Inclusive = true);

	/*
	 * Sorts the given Types by the number of defensible Types within the specified range. For example, if Fire is only weak (defending) to Water, it would be near the end of the list.
	 */
	UFUNCTION(BlueprintCallable)
	static void SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive);

#pragma endregion


	
};
