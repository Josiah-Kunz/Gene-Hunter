#pragma once

// Engine
#include "CoreMinimal.h"

// Stats
#include "LevelComponent/Public/LevelComponent.h"
#include "Health.h"
#include "PhysicalAttack.h"
#include "PhysicalDefense.h"
#include "SpecialAttack.h"
#include "SpecialDefense.h"
#include "Haste.h"
#include "CriticalHit.h"

// Effects
#include "EffectableComponent.h"

// Utilities
#include "ModificationMode.h"
#include "StatEnum.h"
#include "StatRandParams.h"
#include "StatValueType.h"
#include "Outlets/ModifyStatOutlet.h"
#include "Outlets/RandomizeStatsOutlet.h"
#include "Outlets/RecalculateStatsOutlet.h"

// .gen
#include "CombatStatsComponent.generated.h"

/**
 * A class to hold, track, and calculate FCombatStat such as Health, Physical Attack, and Haste, but also
 *	level and exp yield. It should only be used for "invisible" stats (think command line simulator) and *not* be used
 *	for movement modifiers like run speed or jump height.
 */
UCLASS(ClassGroup=(Monster), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Combat Stats"))
class COMBATSTATSCOMPONENT_API UCombatStatsComponent : public UEffectableComponent
{
	
#pragma region Inherited functions
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UCombatStatsComponent();

	virtual void OnComponentCreated() override;
	
	void EnsureLevelComponent(AActor* Owner);

private:

	UPROPERTY();
	FAfterSetCXPDelegate UpdateStatsAfterLevel;

	UFUNCTION(CallInEditor, Category="CombatStats")
	void ChangeStatsOnLevelChange(const uint32 OldCXP, const int32 InputCXP, const int32 AttemptedCXP);

protected:

#pragma endregion

#pragma region Stat variables
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level")
	ULevelComponent* LevelComponent;
	
private:
	
	UPROPERTY()
	FHealth Health;
	
	UPROPERTY()
	FPhysicalAttack PhysicalAttack;

	UPROPERTY()
	FPhysicalDefense PhysicalDefense;

	UPROPERTY()
	FSpecialAttack SpecialAttack;

	UPROPERTY()
	FSpecialDefense SpecialDefense;

	UPROPERTY()
	FHaste Haste;

	UPROPERTY()
	FCriticalHit CriticalHit;

public:

	/**
	 * Gets the read-only FCombatStat by EStatEnum. If you'd like to modify the FStat, use ModifyStat (or similar).
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	FCombatStat& GetStat(const EStatEnum Stat);

	/**
	 * Gets the read-only FCombatStat's value by EStatEnum. If you'd like to modify the FStat, use ModifyStat (or similar).
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	float GetStatValue(const EStatEnum Stat, const EStatValueType ValueType);

private:

	/**
	 * The mutable version of GetStat. Use internally only and only if you really know what you're doing. Otherwise, you
	 * may be modifying FCombatStat without calling Outlets.
	 */
	FCombatStat& GetStatMutable(const EStatEnum Stat);

#pragma endregion

#pragma region Stat arrays

public:

	TArray<EStatEnum> StatsArray = {
		EStatEnum::Health,
		EStatEnum::PhysicalAttack,
		EStatEnum::PhysicalDefense,
		EStatEnum::SpecialAttack,
		EStatEnum::SpecialDefense,
		EStatEnum::Haste,
		EStatEnum::CriticalHit
	};

	TArray<EStatEnum> NonPercentageStats = {
		EStatEnum::Health,
		EStatEnum::PhysicalAttack,
		EStatEnum::PhysicalDefense,
		EStatEnum::SpecialAttack,
		EStatEnum::SpecialDefense
	};

	TArray<EStatEnum> PercentageStats = {
		EStatEnum::Haste,
		EStatEnum::CriticalHit
	};


#pragma endregion

#pragma region Stat manipulation

private:

	/**
	 * Randomizes a single FCombatStat uniformly by randomizing the BaseStats and BasePairs between Min and Max (inclusive).
	 * If any max is greater than its corresponding min, it will be ignored.
	 * All stat randomization goes through this, so the Outlets are called here.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeStat_Internal(const EStatEnum Stat, const FStatRandParams OriginalParams, FStatRandParams Params);

public:

	/**
	 * Randomizes a single FCombatStat uniformly by randomizing the BaseStats and BasePairs between Min and Max (inclusive).
	 * If any max is greater than its corresponding min, it will be ignored.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeStat(const EStatEnum Stat, FStatRandParams Params);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeBasePair(const EStatEnum Stat, const int32 MinBasePairs = 1, const int32 MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeBaseStat(const EStatEnum Stat, const int32 MinBaseStats = 80, const int32 MaxBaseStats = 120);

	/**
	 * Randomizes the Stats uniformly by randomizing the BaseStats and BasePairs between:
	 *	BaseStats: 50--150
	 *	BasePairs: 1--100
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeStats();
	
	/**
	 * Randomizes the Stats uniformly by randomizing the BaseStats and BasePairs between Min and Max (inclusive).
	 * If any max is greater than its corresponding min, it will be ignored.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeStatsCustom(const FStatRandParams Params);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeBasePairs(const int32 MinBasePairs = 1, const int32 MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="CombatStats")
	void RandomizeBaseStats(const int32 MinBaseStats = 80, const int32 MaxBaseStats = 120);

	/**
	 * Before parameters:
	 *  - [const EStatEnum] the stat that is being randomized (the actual function loops over all FCombatStat)
	 *	- [const FStatRandParams] original parameters to be used
	 *	- [FStatRandParams&] parameters that will be used in randomization
	 *
	 *	After parameters:
	 *	- [const EStatEnum] the stat that was randomized (the actual function loops over all FCombatStat)
	 *	- [const FStatRandParams] original parameters that would otherwise be used
	 *	- [const FStatRandParams] parameters that were used
	 *
	 *	Note: All "Randomize" functions call RandomizeStats, which calls this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Level Outlets")
	FRandomizeStatsOutlet RandomizeStatsOutlet;

	/**
	 * Modifies (that is, increases, decreases, or sets) a single Stat in this StatsComponent. Does not call
	 * FCombatStat::Update because the level hasn't changed.
	 */
	void ModifyStat(EStatEnum Stat, const float Value, const EStatValueType ValueType, const EModificationMode Mode,
		const EStatReferenceType ReferenceType = EStatReferenceType::Self, const float ReferenceValue = 0
		);
	
	/**
	 * Modifies (that is, increases, decreases, or sets) the Stats in this StatsComponent. Order is HP, PhA, PhD, SpA, SpD, Hst, Crt.
	 */
	void ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode);

	/**
	 * Before parameters:
	 *  - [const EStatEnum] the stat that is being randomized (the actual function loops over all FCombatStat)
	 *	- [const EStatValueType] the type of value, such as BaseStat or CurrentValue
	 *	- [const EModificationMode] the mode of modification, such as SetDirectly or AddFraction
	 *	- [const float OriginalValue] the value of the stat before modification
	 *	- [float&] the value that is being attempted (and will be set)
	 *
	 *	After parameters:
	 *	- same, but the last parameter is const float NewValue.
	 *
	 *	Note: All "Modify" functions call ModifyStatInternal, which calls this.
	 */
	
	FModifyStatOutlet ModifyStatOutlet;
	
	/**
	 * Modifies (that is, increases, decreases, or sets) all Stats in this StatsComponent by the given amount.
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType, const EModificationMode Mode);
	
	/**
	 * Recalculates all stats based on the current level and resets current stats. Also calls FCombatStat::Update.
	 */
	UFUNCTION(BlueprintCallable)
	void RecalculateStats(const bool bResetCurrent = true, const bool bResetHP = false);

	/**
	 * Before and After parameters are identical:
	 *  - [const EStatEnum] the stat that is being recalculated (the actual function loops over all FCombatStat)
	 *	- [const bool] if true, the current stats will reset (permanent always reset)
	 *	- [const float] the original current stats (prior to recalculation)
	 *	- [const float] the original permanent stats (prior to recalculation)
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FRecalculateStatsOutlet RecalculateStatsOutlet;
	
private:

	/**
	 * All in-code modifications should pass through here rather than doing Stat->ModifyValue(...). This ensures that 
	 * the effect delegates are called.
	 */
	void ModifyStatInternal(EStatEnum Stat, float Value, EStatValueType ValueType, EModificationMode Mode,
		const EStatReferenceType ReferenceType = EStatReferenceType::Self, const float ReferenceValue = 0);

#pragma endregion

#pragma region Utilities

public:
	
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable)
	bool IsEqual(UCombatStatsComponent* Other, const EStatValueType ValueType, const float Tolerance = 0.1f);

	/**
	 * Gets the raw sum of all BaseStats. (In Pokemon, the BST seems to be important, although I've never thought so. Are personal feelings allowed in comments?)
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float BaseStatTotal();

	/**
	 * Calculates the "effective average" of the BaseStats. That is, all Stats are included, except if the attack
	 * (physical or special) is "non-ideal" (less than 10% of the other attack). Defenses are not treated the same way
	 * since both PhysicalDefense and SpecialDefense are always relevant.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float BaseStatEffectiveAverage();

	/**
	 * Returns the value that *would be* modified without actually modifying the Stat.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	float GetModifiedValue(const EStatEnum Stat, const float ModValue, const EStatValueType ValueType,
		const EModificationMode Mode);

	/**
	 * If the given FCombatStat would be reduced, it is instead not reduced. Note: his is a utility function that does only
	 * manipulates Value and does *not* call ModifyStatInternal, so no Outlets are executed.
	 *
	 * @param Value Value to set using this Mode in order to avert reducation. For example, if Value was originally
	 * negative and ValueType was AddAbsolute, the new Value would be zero.
	 */
	void AvertReduction(const EStatEnum Stat, float& Value, const EStatValueType ValueType,
		const EModificationMode Mode);

	/**
		 * If the given FCombatStat would be reduced, it is instead not reduced. Note: his is a utility function that does only
		 * manipulates Value and does *not* call ModifyStatInternal, so no Outlets are executed.
		 *
		 * @param Value Value to consider using this Mode in order to determine harm.
		 * For example, if Value was originally negative and ValueType was AddAbsolute, this would return true.
		 * If Value was 0.5, it would return true for a ValueType of MultiplyAbsolute, but false for AddAbsolute.
		 */
	bool IsHarmful(const EStatEnum Stat, const float Value, const EStatValueType ValueType,
		const EModificationMode Mode);

#pragma endregion
	
};
