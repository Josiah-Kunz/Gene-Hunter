// 

#pragma once

#include "CoreMinimal.h"
#include "GeneHunter/UI/SupportingText.h"
#include "UObject/Object.h"
#include "MathUtil.h" // For inherited classes using, e.g., FMathf::Floor
#include "GeneHunter/Stats/ModificationMode.h"
#include "GeneHunter/Stats/StatGainType.h"
#include "Stat.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UStat : public UObject
{
	GENERATED_BODY()

#pragma region Public variables

public:

	/**
	 * The "base" from which to calculate the CurrentValue or PermanentValue.
	 */
	UPROPERTY()
	int BaseStat = 1;

	/**
	 * The DNA base pair count that augment this Stat. See the Stats document for relevant equations.
	 */
	UPROPERTY()
	int BasePairs = 1;
	
	/**
	 * If true, this Stat is reset when switched out of battle.
	 */
	UPROPERTY()
	bool ResetOnSwitch;

#pragma endregion

#pragma region Protected variables for setters/getters

protected:

	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	UPROPERTY()
	float CurrentValue;

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	UPROPERTY()
	float PermanentValue;

	virtual float StatJump(int Level);

#pragma endregion

#pragma region Public functions for setters/getters

public:
	
	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetCurrentValue();

	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	UFUNCTION(BlueprintCallable)
	void SetCurrentValue(const float NewValue);

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetPermanentValue();

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	UFUNCTION(BlueprintCallable)
	void SetPermanentValue(const float NewValue);

	

#pragma endregion

#pragma region Public functions

public:
	
	/**
	 * Updates the PermanentValue based on the input level.
	 * @param Level The level (always positive).
	 * @param ResetCurrent If true, CurrentValue will match PermanentValue after the calculation is done.
	 */
	UFUNCTION(BlueprintCallable)
	virtual void UpdatePermanent(const int Level, const bool ResetCurrent = true);

	/**
	 * Updates the CurrentValue based on the input level.
	 * @param Level The level (always positive).
	 */
	UFUNCTION(BlueprintCallable)
	virtual void UpdateCurrent(const int Level);

	UFUNCTION(BlueprintCallable)
	virtual void ModifyValue(const float Modifier, const EStatGainType GainType, const EModificationMode ModifyMode);

#pragma endregion

#pragma region Things that should be overridden!

public:
	
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	UFUNCTION(BlueprintCallable)
	virtual float CalculateValue(const int Level);

	/**
		 * This Stat's description and such.
		 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FSupportingText const SupportingText() const;
	
	/**
	 * The name of this Stat to be displayed (such as "Physical Attack").
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FString const Name() const;

	/**
	 * A shorter version of Name (such as "PhA" for "Physical Attack").
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FString const Abbreviation() const;

	/**
	 * The color associated with this Stat.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FLinearColor const Color() const;

#pragma endregion

#pragma region Private functions

private:
	static float GetModification(const int Original, const EModificationMode Mode, const float Modification);

#pragma endregion
	
};
