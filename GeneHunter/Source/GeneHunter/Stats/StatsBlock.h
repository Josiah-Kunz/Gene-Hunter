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
	
public:

	// The Stats
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

	/**
	 * Modifies (that is, increases, decreases, or sets) the Stats in this StatsBlock.
	 */
	UFUNCTION(BlueprintCallable)
	void ModifyStats(TMap<UStat*, int>& ValueMap, const EStatValueType ValueType, const EModificationMode Mode);

	UFUNCTION(BlueprintCallable)
	void ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType, const EModificationMode Mode);

	UFUNCTION(BlueprintCallable)
	bool IsEqual(UStatsBlock* Other, const EStatValueType ValueType, const float Tolerance = 0.1f);

	void GetStatsArray(TArray<UStat*>& Array);
	
};
