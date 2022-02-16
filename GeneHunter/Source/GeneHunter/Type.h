

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

	/*
	 * Gets Types that take increased damage from this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetIncreasedDamageTypes();

	/*
	 * Gets Types that take decreased damage from this Type (not including immune or healed).
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetDecreasedDamageTypes();

	/*
	 * Gets Types that are immune to this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetImmuneTypes();

	/*
	 * Gets Types that are healed instead of damaged when this Type attacks.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetHealedDamageTypes();

	/*
	 * Gets Types that are damaged normally by this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetNeutralDamageTypes();

	/*
	 * Gets Types whose damage modifiers are between Min and Max for this Type.
	 */
	UFUNCTION(BlueprintCallable)
	TArray<UType*> GetDamageTypesBetween(const float Min, const float Max, const bool Inclusive = true);
	
	/**
	 * A map of modifiers that this Type gets when attacking other Types.
	 **/
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TMap<UType*, FAttackModifier> AttackModifiers;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	TArray<FLinearColor> Colors;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	FSupportingText SupportingText;
	
};
