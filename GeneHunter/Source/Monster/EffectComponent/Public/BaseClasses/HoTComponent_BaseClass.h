#pragma once

#include "CoreMinimal.h"
#include "BuffComponent_BaseClass.h"
#include "CombatStatsComponent.h"
#include "HoTComponent_BaseClass.generated.h"


/**
 * A subclass of UBuff that [H]eals [o]ver [T]ime.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UHoTComponent_BaseClass : public UBuffComponent_BaseClass
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * When RemainingTime <= NextModTime, the stat will be modified.
	 */
	float NextModTime = -1;

public:
	
	/**
	 * Retrieves the amount of Health modification per tick rate. Can be positive or negative.
	 */
	virtual float GetAmount();

	/**
	 * Gets "tick rate" (how often Health modification happens in seconds).
	 */
	virtual float GetTickRate();

	virtual void OnComponentCreated() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
