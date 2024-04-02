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
	 * How much health is added (based on Mode).
	 */
	float Amount = 1;

	/**
	 * How often the heal occurs (in seconds).
	 */
	float TickRate = 1;

public:
	
	/**
	 * Retrieves the amount of Health modification per tick rate. Can be positive or negative. Default is +1% and it is
	 * retrieved via StatsComponent's PermanentValue * 0.01 * number of stacks.
	 */
	virtual float GetAmount();

	virtual void OnComponentCreated() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
