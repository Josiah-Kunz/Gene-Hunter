#pragma once

// Engine
#include "CoreMinimal.h"

// Other components
#include "EffectableComponent.h"
#include "AfterSetCXPOutlet.h"

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
	 * Gets the amount of experience this Monster yields when defeated.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	float GetExpYield(ULevelComponent* VictoriousMonster);

#pragma endregion

#pragma region Exp
	
private:
	
	/**
	 * The total experience accumulated points across all levels. Sometimes also called CXP.
	*/
	UPROPERTY()
	int CumulativeExp;

public:

	/**
	 * Gets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int GetCXP();

	/**
	 * Sets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetCXP(int NewCumulativeExp);

private:
	
	UPROPERTY()
	TMap<FAfterSetCXPOutlet, float> AfterSetCXP;

	//DECLARE_AFTER_OUTLET_FUNCTIONS_TwoParams(FAfterSetCXPOutlet, AfterSetCXP, AfterSetCXPDelegate, const int, const int);
	
	void ExecuteAfterSetCXP(const int OldCXP, const int NewCXP)
	{
		AfterSetCXP.ValueSort([](const float PriorityA, const float PriorityB)
		{
			return PriorityA < PriorityB;
		});
		for(auto& Pair : AfterSetCXP)
		{
			if (!Pair.Key.AfterSetCXPDelegate.ExecuteIfBound(OldCXP, NewCXP))
			{
				UE_LOG(LogTemp, Warning, TEXT("Outlet type \"AfterSetCXP\" no longer bound! Surely this is an error."))
			}
		}
	}

public:
	void AddAfterSetCXP(const FAfterSetCXPOutlet Outlet, const float Priority)
	{
		AfterSetCXP.Add(Outlet, Priority);
	}

	/**
	 * Adds to the total accumulated experience points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddExp(int AddedCumulativeExp);

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
	 * Adds to the current level.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void AddLevels(const int AddedLevels);
	
	/**
	 * The maximum level. Overrideable.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	virtual int MaxLevel();
	
	/**
     * The minimum level. Overrideable.
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
    virtual int MinLevel();

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
	static float GetCXPFromLevel(const int TargetLevel);

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
