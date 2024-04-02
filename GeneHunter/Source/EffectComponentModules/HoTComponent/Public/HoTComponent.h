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
	 * How health is added.
	 */
	EModificationMode Mode = EModificationMode::AddPercentage;

	/**
	 * Health per second (based on Mode).
	 */
	float HPS = 1;

public:

	virtual void OnComponentCreated() override;

	virtual void DoEffect() override;

};
