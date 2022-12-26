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
#include "Effects/Public/EffectableComponent.h"

// Utilities
#include "ModificationMode.h"
#include "StatValueType.h"
#include "UtilityFunctionLibrary.h"

// .gen
#include "StatsComponent.generated.h"

/**
 * A class to hold, track, and calculate FStats such as Health, Physical Attack, and Haste, but also
 *	level and exp yield. It should only be used for "invisible" stats (think command line simulator) and *not* be used
 *	for movement modifiers like run speed or jump height.
 */
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

#pragma region Stat variables
public:

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Current Stats")
	// TODO
	ULevelComponent* LevelComponent;
	
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
