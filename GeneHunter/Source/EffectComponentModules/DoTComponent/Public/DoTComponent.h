#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "CombatStatsComponent.h"
#include "DoTComponent.generated.h"


/**
 * A subclass of UDebuff that [D]amages [o]ver [T]ime.
 */
UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DOTCOMPONENT_API UDoTComponent : public UBuffComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * How health is added.
	 */
	virtual EModificationMode Mode();

	/**
	 * Damage per second (actual value is based on Mode).
	 */
	virtual float DPS();

	virtual void BeginPlay() override;

	virtual void DoEffect() override;
};
