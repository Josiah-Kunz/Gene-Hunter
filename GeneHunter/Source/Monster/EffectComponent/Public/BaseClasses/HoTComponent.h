﻿#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "StatsComponent.h"
#include "HoTComponent.generated.h"


/**
 * A subclass of UBuff that [H]eals [o]ver [T]ime.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UHoTComponent : public UBuffComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;

	/**
	 * When RemainingTime <= NextModTime, the stat will be modified.
	 */
	int NextModTime = -1;

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
