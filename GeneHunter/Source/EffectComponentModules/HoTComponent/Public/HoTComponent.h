#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "CombatStatsComponent.h"
#include "HoTComponent.generated.h"


/**
 * A subclass of UBuff that [H]eals [o]ver [T]ime.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOTCOMPONENT_API UHoTComponent : public UBuffComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * When RemainingTime <= NextModTime, the stat will be modified.
	 */
	float NextModTime = -1;

	/**
	 * How health is added.
	 */
	EModificationMode Mode = EModificationMode::AddPercentage;

	/**
	 * Health per second (based on Mode).
	 */
	float HPS = 1;

	/**
	 * How often the heal occurs (in seconds).
	 */
	float TickDuration = 1;

public:

	virtual void OnComponentCreated() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
