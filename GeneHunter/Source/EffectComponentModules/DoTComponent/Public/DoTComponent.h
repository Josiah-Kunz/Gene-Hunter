#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "CombatStatsComponent.h"
#include "DoTComponent.generated.h"


/**
 * A subclass of UDebuff that [D]amages [o]ver [T]ime.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DOTCOMPONENT_API UDoTComponent : public UBuffComponent
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
	 * Retrieves the amount of Health modification per tick rate. Can be positive or negative. Default is -1%.
	 */
	virtual float GetAmount();

	/**
	 * Gets "tick rate" (how often Health modification happens in seconds).
	 */
	virtual float GetTickRate();

	virtual void OnComponentCreated() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};
