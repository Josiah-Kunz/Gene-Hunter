#pragma once

// Engine
#include "CoreMinimal.h"

// Outlets
#include "Outlets/GetBaseExpYieldOutlet.h"
#include "Outlets/GetCXPOutlet.h"
#include "Outlets/SetBaseExpYieldOutlet.h"
#include "Outlets/SetCXPOutlet.h"
#include "Outlets/GetExpYieldOutlet.h"
#include "Outlets/GetMaxLevelOutlet.h"
#include "Outlets/GetMinLevelOutlet.h"

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
	float GetBaseExpYield();

	/**
	 * Before Parameters:
	 *	- [const float] original yield prior to modification
	 *	- [float&] yield that is being set and then returned
	 *
	 *	After Parameters:
	 *	- [const float] original yield prior to modification
	 *	- [const float] yield that is being returned
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetBaseExpYieldOutlet GetBaseExpYieldOutlet;
	
	/**
	 * Sets the value of BaseExpYield.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetBaseExpYield(float NewBaseExpYield);

	/**
	 * Before parameters:
	 *	- [const float] original yield prior to setting
	 *	- [const float] input yield that's trying to be set
	 *	- [float&] amount that will actually be set
	 *
	 *	After parameters:
	 *	- [const float] original yield prior to setting
	 *	- [const float] input yield that would have been set if no Outlets existed
	 *	- [const float] newly set yield
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FSetBaseExpYieldOutlet SetBaseExpYieldOutlet;

	/**
	 * Gets the amount of experience this Monster yields when defeated.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetExpYield(ULevelComponent* VictoriousMonster);

	/**
	 * Before parameters:
	 *	- [const float] original yield from documented calculations
	 *	- [float&] returned yield
	 *	- [const uint16] level of the Monster that was defeated (and hence yielding the points)
	 *	- [const uint16] level of the Monster that was victorious (and hence receives the points)
	 *
	 * After parameters:
	 *	- [const float] original yield from documented calculations
	 *	- [const float] returned yield
	 *	- [const uint16] level of the Monster that was defeated (and hence yielding the points)
	 *	- [const uint16] level of the Monster that was victorious (and hence receives the points)
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetExpYieldOutlet GetExpYieldOutlet;

#pragma endregion

#pragma region Exp
	
private:
	
	/**
	 * The total experience accumulated points across all levels. Sometimes also called CXP.
	*/
	UPROPERTY()
	uint32 CumulativeExp = 1;

public:

	/**
	 * Gets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetCXP();

	/**
	 * Before Parameters:
	 *	- [const uint32] CXP prior to modification
	 *	- [int32&] attempted CXP that is being set
	 *
	 * After Parameters:
	 *	- [const uint32] CXP prior to modification
	 *	- [const uint32] CXP that is being set
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetCXPOutlet GetCXPOutlet;

	/**
	 * Sets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetCXP(int32 NewCumulativeExp);

	/**
	 * Before parameters:
	 *	- [const uint32] CXP prior to modification
	 *	- [int32&] attempted CXP that is being set
	 *
	 *	After parameters:
	 *	- [const uint32] CXP prior to modification
	 *	- [const int32] CXP that was set
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FSetCXPOutlet SetCXPOutlet;

	/**
	 * Adds to the total accumulated experience points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddExp(int32 AddedCumulativeExp);

#pragma endregion

#pragma region Level

public:

	/**
	 * Gets the current level based on the amount of cumulative experience points.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetLevel();

	/**
	 * Retrieves the level from the given amount of cumulative experience points.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static int32 GetLevelFromCXP(const int32 CXP);
	
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetLevel(int32 NewLevel);

	/**
	 * Adds to the current level.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddLevels(const int32 AddedLevels);
	
	/**
	 * The maximum level. Overrideable.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	virtual int32 GetMaxLevel();

	/**
	 * Before parameters:
	 *	- [const uint16] default max
	 *	- [int32&] attempted max that is being set
	 *
	 *	After parameters:
	 *	- [const uint16] default max
	 *	- [const int32] max that was set
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetMaxLevelOutlet GetMaxLevelOutlet;
	
	/**
     * The minimum level. Overrideable.
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
    virtual int32 GetMinLevel();

	/**
	 * Before parameters:
	 *	- [const uint16] default min
	 *	- [int32&] attempted min that is being set
	 *
	 *	After parameters:
	 *	- [const uint16] default min
	 *	- [const int32] min that was set
	 */
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FGetMinLevelOutlet GetMinLevelOutlet;

#pragma endregion

#pragma region Conversion: exp <-> level

public:

	/**
	* The relationship between level and CumulativeExp is:
	*	CumulativeExp = Level ^ ExpExponent
	*/
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static float ExpExponent();

	/**
	 * Retrieves the minimum amount of (cumulative) experience points required for the target level.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	static int32 GetCXPFromLevel(const int32 TargetLevel);

	/**
	 * Gets the additional experience points required for the next level, taking current exp into account.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetExpToLevel();

	/**
	 * Gets the experience points required from the previous level to the next level. Useful for display purposes.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetTotalLevelExp();

	/**
	 * Gets the amount of (non-cumulative) experience points into this level. Useful for display purposes.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetLevelExp();

	/**
	 * Gets the amount of cumulative exp at max level.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetMaxExp();

#pragma endregion
	
};
