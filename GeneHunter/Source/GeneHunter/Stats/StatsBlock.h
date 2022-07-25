#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "GeneHunter/Stats/Health.h"
#include "GeneHunter/Stats/PhysicalAttack.h"
#include "GeneHunter/Stats/PhysicalDefense.h"
#include "GeneHunter/Stats/SpecialAttack.h"
#include "GeneHunter/Stats/SpecialDefense.h"
#include "GeneHunter/Stats/Haste.h"
#include "GeneHunter/Stats/CriticalHit.h"

#include "StatsBlock.generated.h"

UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class GENEHUNTER_API UStatsBlock : public UActorComponent
{
#pragma region Standard stuff
	
	GENERATED_BODY()

public:
	
	// Sets default values for this component's properties
	UStatsBlock();

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
	int Level = 1;
	
	UFUNCTION(CallInEditor)
	void SetLevel(int Value)
	{
		Level = Value;
		TArray<UStat*> StatsArray;
		GetStatsArray(StatsArray);
		for(UStat* Stat : StatsArray)
			Stat->Update(Level);
	}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced, Category = "Stats")
	UHealth* Health = CreateDefaultSubobject<UHealth>("Health");
	
	UPROPERTY()
	UPhysicalAttack* PhysicalAttack = NewObject<UPhysicalAttack>();

	UPROPERTY()
	UPhysicalDefense* PhysicalDefense = NewObject<UPhysicalDefense>();

	UPROPERTY()
	USpecialAttack* SpecialAttack = NewObject<USpecialAttack>();

	UPROPERTY()
	USpecialDefense* SpecialDefense = NewObject<USpecialDefense>();

	UPROPERTY()
	UHaste* Haste = NewObject<UHaste>();

	UPROPERTY()
	UCriticalHit* CriticalHit = NewObject<UCriticalHit>();

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
	 * Modifies (that is, increases, decreases, or sets) the Stats in this StatsBlock.
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyStats(TMap<UStat*, int>& ValueMap, const EStatValueType ValueType, const EModificationMode Mode);

	/**
	 * Modifies (that is, increases, decreases, or sets) all Stats in this StatsBlock by the given amount.
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
	bool IsEqual(UStatsBlock* Other, const EStatValueType ValueType, const float Tolerance = 0.1f);

	/**
	 * Gets the array of Stats, e.g., {Health, PhysicalAttack, ...}.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void GetStatsArray(TArray<UStat*>& Array);

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
