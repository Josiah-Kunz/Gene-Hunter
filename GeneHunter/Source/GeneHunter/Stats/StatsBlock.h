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
	
	UPROPERTY()
	UHealth* Health = NewObject<UHealth>();
	
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

	/**
	 * Randomizes the Stats uniformly by randomizing the BaseStats and BasePairs between Min and Max (inclusive).
	 * If any max is greater than its corresponding min, it will be ignored.
	 */
	UFUNCTION(BlueprintCallable)
	void RandomizeStats(
		const int Level = 1,
		const int MinBaseStat = 50, const int MaxBaseStat = 150,
		const int MinBasePairs = 1, const int MaxBasePairs = 100);

	UFUNCTION(BlueprintCallable)
	void RandomizeBasePairs(const int Level = 1, const int MinBasePairs = 1, const int MaxBasePairs = 100);
	
	UFUNCTION(BlueprintCallable)
	void RandomizeBaseStats(const int Level = 1, const int MinBaseStats = 1, const int MaxBaseStats = 100);
	
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
	void GetStatsArray(TArray<UStat*>& Array);

#pragma endregion
	
};
