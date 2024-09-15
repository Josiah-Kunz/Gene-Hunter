#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "CombatStatsComponent.h"
#include "HoTComponent.generated.h"


/**
 * A subclass of UBuff that [H]eals [o]ver [T]ime.
 */
UCLASS(Abstract, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HOTCOMPONENT_API UHoTComponent : public UBuffComponent
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
	 * When we say "x%", what do we mean? Percentage of what?
	 */
	virtual EStatReferenceType StatReferenceType();

	/**
	 * Health per second (actual value is based on Mode).
	 */
	virtual float HPS();

	virtual void InitializeEffect() override;

	virtual void DoEffect() override;

};
