#pragma once

// Engine
#include "CoreMinimal.h"

// Other components
#include "EffectableComponent.h"
#include "AfterSetCXPOutlet.h"
#include "BeforeSetCXPOutlet.h"

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
	 * Sets the value of BaseExpYield.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetBaseExpYield(float NewBaseExpYield);

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
	uint32 CumulativeExp;

public:

	/**
	 * Gets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
	int32 GetCXP();

	/**
	 * Sets the total experience accumulated points across all levels.
	 */
	UFUNCTION(BlueprintCallable, Category="Level")
	void SetCXP(int32 NewCumulativeExp);

	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FBeforeSetCXPOutlet BeforeSetCXPOutlet;
	
	UPROPERTY(VisibleAnywhere, Category="Level Outlets")
	FAfterSetCXPOutlet AfterSetCXPOutlet;
	
	/*
	void ExecuteAfterSetCXP(const int OldCXP, const int NewCXP)
	{
		for(FAfterSetCXPOutlet& Outlet : AfterSetCXP)
		{
			if (!Outlet.Delegate.ExecuteIfBound(OldCXP, NewCXP))
			{
				UE_LOG(LogTemp, Warning, TEXT("Outlet type \"AfterSetCXP\" no longer bound! Surely this is an error."))
			}
		}
	}

public:
	void AddAfterSetCXP(const FAfterSetCXPOutlet NewOutlet, const float Priority)
	{
		bool bAdded = false;
		for(int i=0; i<AfterSetCXP.Num(); i++)
		{
			if (Priority < AfterSetCXP[i].Priority)
			{
				AfterSetCXP.Insert(NewOutlet, i);
				bAdded = true;
			}
		}
		if (!bAdded)
			AfterSetCXP.Add(NewOutlet);
	}
	*/

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
	virtual int32 MaxLevel();
	
	/**
     * The minimum level. Overrideable.
     */
    UFUNCTION(BlueprintCallable, BlueprintPure, Category="Level")
    virtual int32 MinLevel();

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
