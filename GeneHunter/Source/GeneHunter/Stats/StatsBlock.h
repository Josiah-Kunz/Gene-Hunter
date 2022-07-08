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

#include "GeneHunter/Stats/StatGainMode.h"

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
	UHealth Health;
	UPhysicalAttack PhysicalAttack;
	UPhysicalDefense PhysicalDefense;
	USpecialAttack SpecialAttack;
	USpecialDefense SpecialDefense;
	UHaste Haste;
	UCriticalHit CriticalHit;

	UFUNCTION(BlueprintCallable)
	void GainStats(TArray<int>& Gains, const EStatGainMode Mode);

	UFUNCTION(BlueprintCallable)
	void GainStats(const TMap<UStat*, int> Gains, const EStatGainMode Mode);

private:

	bool CheckGainsNum(int Length);
	
	void StatsArray(TArray<UStat*>& Array);

	void GainStatsInternal(TArray<UStat*>& StatsArray, TArray<int>& Gains, const EStatGainMode Mode);
	
};
