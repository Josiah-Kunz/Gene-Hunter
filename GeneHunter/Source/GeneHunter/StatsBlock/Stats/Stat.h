#pragma once

#include "CoreMinimal.h"
#include "GeneHunter/UI/SupportingText.h"
#include "UObject/Object.h"
#include "MathUtil.h" // For inherited classes using, e.g., FMathf::Floor
#include "GeneHunter/GeneHunterBPLibrary.h" // For inherited classes using, e.g., RoundToDecimal
#include "GeneHunter/StatsBlock/ModificationMode.h"
#include "GeneHunter/StatsBlock/StatValueType.h"
#include "Stat.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct GENEHUNTER_API FStat
{
	GENERATED_BODY()

#pragma region Public variables

public:
	
	/**
	 * The "base" from which to calculate the CurrentValue or PermanentValue.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BaseStat = 1;

	/**
	 * The DNA base pair count that augment this Stat. See the Stats document for relevant equations.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int BasePairs = 1;

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

	virtual float StatJump(const int Level);

#pragma endregion

#pragma region Public functions for setters/getters

public:
	
	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	float GetCurrentValue();

	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	void SetCurrentValue(const float NewValue);

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	float GetPermanentValue();

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	void SetPermanentValue(const float NewValue);

#pragma endregion

#pragma region Public functions

public:

	FStat();

	/**
	 * Updates both PermanentValue and CurrentValue (in that order) based on the level.
	 */
	virtual void Update(const int Level);
	
	/**
	 * Updates the PermanentValue based on the input level.
	 * @param Level The level (always positive).
	 * @param ResetCurrent If true, CurrentValue will match PermanentValue after the calculation is done.
	 */
	virtual void UpdatePermanent(const int Level, const bool ResetCurrent = true);

	/**
	 * Updates the CurrentValue based on the input level.
	 * @param Level The level (always positive).
	 */
	virtual void UpdateCurrent(const int Level);

	virtual void ModifyValue(const float Modifier, const EStatValueType ModifyType, const EModificationMode ModifyMode);

	FString ToString(const bool Inline = true);

#pragma endregion

#pragma region Things that should be overridden!

public:
	
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	virtual float CalculateValue(const int Level);

	/**
	 * This Stat's description and such.
	 */
	virtual FSupportingText const SupportingText() const;
	
	/**
	 * The name of this Stat to be displayed (such as "Physical Attack").
	 */
	virtual FString const Name() const;

	/**
	 * A shorter version of Name (such as "PhA" for "Physical Attack").
	 */
	virtual FString const Abbreviation() const;

	/**
	 * The color associated with this Stat.
	 */
	virtual FLinearColor const Color() const;

#pragma endregion

#pragma region Private functions

private:
	static float GetModification(const int Original, const EModificationMode Mode, const float Modification);

#pragma endregion
	
};
