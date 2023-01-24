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
#include "StatValueType.h"

// .gen
#include "StatsComponent.generated.h"

/**
 * A class to hold, track, and calculate FStats such as Health, Physical Attack, and Haste, but also
 *	level and exp yield. It should only be used for "invisible" stats (think command line simulator) and *not* be used
 *	for movement modifiers like run speed or jump height.
 */
UCLASS(ClassGroup=(Monster), BlueprintType, meta=(BlueprintSpawnableComponent,
	ShortTooltip = "Combat Stats"))
class STATSCOMPONENT_API UStatsComponent : public UEffectableComponent
{
	
#pragma region Inherited functions
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UStatsComponent();

	virtual void OnComponentCreated() override;

	void EnsureLevelComponent(AActor* Owner);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

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

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	FStat& GetStat(const EStatEnum Stat);

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

public:
	
	/**
	 * Randomizes the Stats uniformly by randomizing the BaseStats and BasePairs between Min and Max (inclusive).
	 * If any max is greater than its corresponding min, it will be ignored.
	 */
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeStats(
		int MinBaseStat = 50, int MaxBaseStat = 150,
		int MinBasePairs = 1, int MaxBasePairs = 100);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBasePairs(const int MinBasePairs = 1, const int MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBaseStats(const int MinBaseStats = 80, const int MaxBaseStats = 120);

	/**
	 * Modifies (that is, increases, decreases, or sets) a single Stat in this StatsComponent.
	 */
	void ModifyStat(EStatEnum Stat, const float Value, const EStatValueType ValueType, const EModificationMode Mode);
	
	
	/**
	 * Modifies (that is, increases, decreases, or sets) the Stats in this StatsComponent. Order is HP, PhA, PhD, SpA, SpD, Hst, Crt.
	 */
	void ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode);
	
	/**
	 * Modifies (that is, increases, decreases, or sets) all Stats in this StatsComponent by the given amount.
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType, const EModificationMode Mode);
	
	/**
	 * Recalculates all stats based on the current level and resets current stats.
	 */
	UFUNCTION(BlueprintCallable)
	void RecalculateStats(bool bResetCurrent = true);
	
private:

	/**
	 * All in-code modifications should pass through here rather than doing Stat->ModifyValue(...). This ensures that 
	 * the effect delegates are called.
	 */
	void ModifyStatInternal(EStatEnum Stat, float Value, EStatValueType ValueType, EModificationMode Mode);

#pragma endregion

#pragma region Utilities

public:
	
	/**
	 *
	 */
	UFUNCTION(BlueprintCallable)
	bool IsEqual(UStatsComponent* Other, const EStatValueType ValueType, const float Tolerance = 0.1f);

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
	 * If the given FStat would be reduced, it is instead not reduced.
	 */
	void AvertReduction(EStatEnum Stat, float& Value, const EStatValueType ValueType,
		const EModificationMode Mode);

#pragma endregion
	
};
