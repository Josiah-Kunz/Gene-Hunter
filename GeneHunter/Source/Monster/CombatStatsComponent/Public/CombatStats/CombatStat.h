#pragma once

#include "CoreMinimal.h"
#include "ModificationMode.h"
#include "StatReferenceType.h"
#include "StatValueType.h"
#include "SupportingText.h"

#include "CombatStat.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FCombatStat
{
	GENERATED_BODY()

#pragma region Public variables

public:
	virtual ~FCombatStat() = default;

	/**
	 * The "base" from which to calculate the CurrentValue or PermanentValue.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BaseStat = 1;

	/**
	 * The DNA base pair count that augment this Stat. See the Stats document for relevant equations.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 BasePairs = 1;

#pragma endregion

#pragma region Protected variables for setters/getters

protected:

	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level")
	float CurrentValue = 0;

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level")
	float PermanentValue = 1;

	virtual float StatJump(const uint16 Level);

#pragma endregion

#pragma region Public functions for setters/getters

public:
	
	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	float GetCurrentValue() const;

	/**
	 * The current value of this Stat that can be increased or decreased. CurrentValue reverts to PermanentValue, e.g.,
	 * at the start and end of a battle.
	 */
	void SetCurrentValue(const float NewValue);

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	float GetPermanentValue() const;

	/**
	 * The default value of this Stat, e.g., when a battle starts. Only modify outside of battle (e.g., on level).
	 */
	void SetPermanentValue(const float NewValue);

#pragma endregion

#pragma region Public functions

public:

	/**
	 * Updates both PermanentValue and CurrentValue (in that order) based on the level.
	 */
	virtual void Update(const uint16 Level, const bool bResetCurrent = true);
	
	/**
	 * Updates the PermanentValue based on the input level.
	 * @param Level The level (always positive).
	 * @param ResetCurrent If true, CurrentValue will match PermanentValue after the calculation is done.
	 */
	virtual void UpdatePermanent(const uint16 Level, const bool ResetCurrent = true);

	/**
	 * Updates the CurrentValue based on the input level.
	 * @param Level The level (always positive).
	 */
	virtual void UpdateCurrent(const uint16 Level);

	virtual void ModifyValue(const float Modifier, const EStatValueType ModifyType, const EModificationMode ModifyMode,
		const EStatReferenceType ReferenceType = EStatReferenceType::Self, const float ReferenceValue = 0);

	/**
	 * Gets a "value" associated with this Stat (e.g., BaseStat, PermanentValue, etc.). Useful for, e.g., modular drawers.
	 */
	virtual float GetValue(const EStatValueType ModifyType) const;

	FString ToString(const bool Inline = true) const;

	void RandomizeBaseStat(const int32 Min = 50, const int32 Max = 150);
	
	void RandomizeBasePairs(const int32 Min = 1, const int32 Max = 100);

	/**
	 * Gets the modification based on the Mode.
	 *
	 * @param ReferenceType only useful when using percentage or fractional values.
	 * @param ReferenceValue should only be used when ReferenceType is SpecifiedValue.
	 */
	float GetModification(const float Original, const EModificationMode Mode, const float Modification,
		const EStatReferenceType ReferenceType = EStatReferenceType::Self, const float ReferenceValue = 0);

#pragma endregion

#pragma region Things that should be overridden!

public:
	
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	virtual float CalculateValue(const uint16 Level);

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

float GetReferenceValue(const float SelfValue, const EStatReferenceType ReferenceType, const float OtherValue);

#pragma endregion
	
};
