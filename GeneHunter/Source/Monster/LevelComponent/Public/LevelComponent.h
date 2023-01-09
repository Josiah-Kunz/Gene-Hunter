#pragma once

// Engine
#include "CoreMinimal.h"

// Other components
#include "EffectableComponent.h"

// .gen
#include "LevelComponent.generated.h"

/**
 * A class to hold, track, and calculate level, current exp, cumulative exp, and exp yield. 
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class LEVELCOMPONENT_API ULevelComponent : public UEffectableComponent
{
	
#pragma region Standard stuff
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	ULevelComponent();

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
	float GetExpYield(ULevelComponent* VictoriousMonster);

	EFFECT_DELEGATES_TwoParams(GetExpYield, ULevelComponent*, float&)

#pragma endregion

#pragma region Exp
	
public:

	/**
	 * The total experience accumulated points across all levels.
	 */
	UPROPERTY(VisibleDefaultsOnly, Category = "Level", meta=(AllowPrivateAccess))
	int CumulativeExp = 33;

public:

	/**
	 * Gets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetCumulativeExp();

	/**
	 * Parameters:
	 *	- Current CXP
	 */
	EFFECT_DELEGATES_OneParam(GetCumulativeExp, int&)

	/**
	 * Sets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetCumulativeExp(int NewCumulativeExp);

	/**
	 * The ultimate root of adding/setting/changing level or experience points. Parameters:
	 *	- Current CXP
	 *	- Attempted CXP
	 */
	EFFECT_DELEGATES_TwoParams(SetCumulativeExp, int, int&)

	/**
	 * Adds to the total accumulated experience points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddExp(int AddedCumulativeExp);

	/**
	 * Goes though SetCumulativeExp. Parameters:
	 *	- Current exp
	 *	- Added exp
	 */
	EFFECT_DELEGATES_TwoParams(AddExp, int, int&)

#pragma endregion

#pragma region Level

public:

	/**
	 * Gets the current level based on the amount of cumulative experience points.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetLevel();

	/**
	 * Retrieves the level from the given amount of cumulative experience points.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static int GetLevelFromCXP(const int CXP);
	
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetLevel(int NewLevel);

	/**
	 * Goes though SetCumulativeExp. Parameters:
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
