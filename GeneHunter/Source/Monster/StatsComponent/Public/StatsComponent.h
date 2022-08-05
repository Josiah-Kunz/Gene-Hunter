#pragma once

// Engine
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// Stats
#include "Health.h"
#include "PhysicalAttack.h"
#include "PhysicalDefense.h"
#include "SpecialAttack.h"
#include "SpecialDefense.h"
#include "Haste.h"
#include "CriticalHit.h"

// Utilities
#include "ModificationMode.h"
#include "StatValueType.h"
#include "StatModStruct.h"

// .gen
#include "StatsComponent.generated.h"

UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class STATSCOMPONENT_API UStatsComponent : public UActorComponent
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

#pragma region The Stat variables
public:

# define CATEGORY_NAME \
	"Stats"

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	int Level = 1;
	
	UFUNCTION(CallInEditor)
	void SetLevel(const int Value);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FHealth Health;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FPhysicalAttack PhysicalAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FPhysicalDefense PhysicalDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FSpecialAttack SpecialAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FSpecialDefense SpecialDefense;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
	FHaste Haste;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CATEGORY_NAME)
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
		const int MinBaseStat = 50, const int MaxBaseStat = 150,
		const int MinBasePairs = 1, const int MaxBasePairs = 100);

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBasePairs(const int MinBasePairs = 1, const int MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Stats")
	void RandomizeBaseStats(const int MinBaseStats = 50, const int MaxBaseStats = 150);
	
	/**
	 * Modifies (that is, increases, decreases, or sets) the Stats in this StatsComponent. Order is HP, PhA, PhD, SpA, SpD, Hst, Crt.
	 */
	void ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode) const;
	
	/**
	 * Modifies (that is, increases, decreases, or sets) all Stats in this StatsComponent by the given amount.
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType, const EModificationMode Mode);

#pragma endregion

#pragma region Details panel buttons

public:
	
	UFUNCTION(BlueprintCallable, CallInEditor, Category="Randomize Stats", meta=(DisplayName="Randomize Everything"))
	void RandomizeStats_DetailsPanel();

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Randomize Stats", meta=(DisplayName="Randomize Base Pairs Only"))
	void RandomizeBasePairs_DetailsPanel();

	UFUNCTION(BlueprintCallable, CallInEditor, Category="Randomize Stats", meta=(DisplayName="Randomize Base Stats Only"))
	void RandomizeBaseStats_DetailsPanel();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomize Stats", meta=(DisplayName="Min Base Pairs"))
	int MinBasePairs_DetailsPanel = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomize Stats", meta=(DisplayName="Max Base Pairs"))
	int MaxBasePairs_DetailsPanel = 100;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomize Stats", meta=(DisplayName="Min Base Stats"))
	int MinBaseStats_DetailsPanel = 50;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Randomize Stats", meta=(DisplayName="Max Base Stats"))
	int MaxBaseStats_DetailsPanel = 150;

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
