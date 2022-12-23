#pragma once

// Engine
#include "CoreMinimal.h"

// Stats
#include "Health.h"
#include "PhysicalAttack.h"
#include "PhysicalDefense.h"
#include "SpecialAttack.h"
#include "SpecialDefense.h"
#include "Haste.h"
#include "CriticalHit.h"

// Effects
#include "Effects/Public/EffectableComponent.h"

// Utilities
#include "ModificationMode.h"
#include "StatValueType.h"
#include "UtilityFunctionLibrary.h"

// .gen
#include "StatsComponent.generated.h"

UCLASS(ClassGroup=(Monster))
class STATSCOMPONENT_API UStatsComponent : public UEffectableComponent
{
	
#pragma region Standard stuff
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UStatsComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Level variables and functions

#pragma region Base exp yield
	
private:

	/**
	 * Linearly multiplies the amount of experience points yielded when defeating this Monster.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level")
	float BaseExpYield = 1;

public:

	/**
	 * Linearly multiplies the amount of experience points yielded when defeating this Monster.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetBaseExpYield();

	/**
	 * Sets the value of BaseExpYield.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetBaseExpYield(int NewBaseExpYield);

	/**
	 * Parameters:
	 *	- Unaltered base exp yield
	 */
	EFFECT_DELEGATES_OneParam(GetBaseExpYield, int)

	/**
	 * Parameters:
	 *	- Unaltered base exp yield
	 *	- The attempted value that's being set
	 */
	EFFECT_DELEGATES_TwoParams(SetBaseExpYield, int, int&)
	
private:

	/**
	 * The total experience accumulated points across all levels.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level")
	int CumulativeExp = 1;

public:

	/**
	 * Gets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetCumulativeExp();

	/**
	 * Parameters:
	 *	- Current CEXP
	 */
	EFFECT_DELEGATES_OneParam(GetCumulativeExp, int&)

	/**
	 * Sets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetCumulativeExp(int NewCumulativeExp);

	/**
	 * Parameters:
	 *	- Current CEXP
	 *	- Attempted CEXP
	 */
	EFFECT_DELEGATES_TwoParams(SetCumulativeExp, int, int&)

	/**
	 * Adds to the total accumulated experience points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddExp(int AddedCumulativeExp);

	/**
	 * Parameters:
	 *	- Current exp
	 *	- Added exp
	 */
	EFFECT_DELEGATES_TwoParams(AddExp, int, int&)

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetLevel();
	
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetLevel(int NewLevel);

	/**
	 * Parameters:
	 *	- Current level
	 *	- Attempted level to set
	 */
	EFFECT_DELEGATES_TwoParams(SetLevel, int, int&)

	/**
	 * Adds to the current level.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddLevels(const int AddedLevels);
	
	/**
	 * The maximum level. Overrideable.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	virtual int MaxLevel();

	EFFECT_DELEGATES_OneParam(MaxLevel, int&)
	
	/**
     * The minimum level. Overrideable.
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
    virtual int MinLevel();

	EFFECT_DELEGATES_OneParam(MinLevel, int&)

	/**
	* The relationship between level and cumulativeExp is:
	*	CumulativeExp = Level ^ ExpExponent
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static float ExpExponent();

	/**
	 * Retrieves the minimum amount of (cumulative) experience points required for the target level.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static float GetCumulativeExpFromLevel(const int TargetLevel);

	/**
	 * Gets the additional experience points required for the next level, taking current exp into account.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetExpToLevel();

	/**
	 * Gets the experience points required from the previous level to the next level. Useful for display purposes.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetTotalLevelExp();

	/**
	 * Gets the amount of (non-cumulative) experience points into this level. Useful for display purposes.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetLevelExp();

	/**
	 * Gets the amount of cumulative exp at max level.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetMaxExp();

	/**
	 * Gets the amount of experience this Monster yields when defeated.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetExpYield(UStatsComponent* VictoriousMonster);

	EFFECT_DELEGATES_TwoParams(GetExpYield, UStatsComponent*, float&)

#pragma endregion

#pragma region Stat variables
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FHealth Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FPhysicalAttack PhysicalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FPhysicalDefense PhysicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FSpecialAttack SpecialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FSpecialDefense SpecialDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FHaste Haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	FCriticalHit CriticalHit;

#pragma endregion

#pragma region Stat arrays

public:

	TArray<FStat*> StatsArray = {
		&Health,
		&PhysicalAttack,
		&PhysicalDefense,
		&SpecialAttack,
		&SpecialDefense,
		&Haste,
		&CriticalHit
	};

	TArray<FStat*> NonPercentageStats = {
		&Health,
		&PhysicalAttack,
		&PhysicalDefense,
		&SpecialAttack,
		&SpecialDefense
	};

	TArray<FStat*> PercentageStats = {
		&Haste,
		&CriticalHit
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

	EFFECT_DELEGATES_FourParams(RandomizeStats, int&, int&, int&, int&)

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBasePairs(const int MinBasePairs = 1, const int MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBaseStats(const int MinBaseStats = 80, const int MaxBaseStats = 120);
	
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

	EFFECT_DELEGATES_TwoParams(RecalculateStats, FStat*, bool)

private:

	/**
	 * All in-code modifications should pass through here rather than doing Stat->ModifyValue(...). This ensures that 
	 * the effect delegates are called.
	 */
	void ModifyStatInternal(FStat* Stat, float Value, EStatValueType ValueType, EModificationMode Mode);

public:
	
	EFFECT_DELEGATES_FourParams(
		ModifyStat,
		FStat*
		, float&				
		, EStatValueType&		
		, EModificationMode&)

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

#pragma endregion
	
};
