#pragma once

// Engine
#include "CoreMinimal.h"

// Effects
#include "Effects/Public/EffectableComponent.h"

// Utilities
#include "UtilityFunctionLibrary.h"

// .gen
#include "StatsComponent.generated.h"

/**
 * A class to hold, track, and calculate level, current exp, cumulative exp, and exp yield. 
 */
UCLASS(ClassGroup=(Monster))
class LEVELCOMPONENT_API ULevelComponent : public UEffectableComponent
{
	
#pragma region Standard stuff
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	ULevelComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override;

#pragma endregion

#pragma region Exp yield
	
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

	/**
	 * Gets the amount of experience this Monster yields when defeated.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetExpYield(UStatsComponent* VictoriousMonster);

	EFFECT_DELEGATES_TwoParams(GetExpYield, UStatsComponent*, float&)

#pragma endregion

#pragma region Exp
	
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

#pragma endregion

#pragma region Level

public:

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

#pragma endregion

#pragma region Conversion: exp <-> level

public:

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

#pragma endregion
	
};
