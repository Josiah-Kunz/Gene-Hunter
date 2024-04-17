#pragma once

#include "CombatStatsComponent.h"
#include "CoreMinimal.h"
#include "TalentEffectComponent.h"
#include "Outlets/RandomizeStatsOutlet.h"

#include "NaturalSelector.generated.h"

/**
 * +20% max health
 */
UCLASS(ClassGroup=(Effects, Talents), meta=(BlueprintSpawnableComponent))
class TALENTEFFECTCOMPONENT_API UNaturalSelector : public UTalentEffectComponent
{
	GENERATED_BODY()
	
private:

	UPROPERTY()
	TMap<EStatEnum, float> OriginalBPValues;

	UFUNCTION()
	void SetBasePairsMin(const EStatEnum TargetStat, const FStatRandParams OriginalParams,
		FStatRandParams& ParamsToBeUsed);
	
public:

	inline static constexpr float MinBasePairs = 75;

	/**
	 * Since the primary goal of this effect is to modify stats, we'll need this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * This is the delegate that attaches to UCombatStatComponent's BeforeModifyStat Outlet.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Outlets", meta = (AllowPrivateAccess = "true"))
	FBeforeRandomizeStatsDelegate BasePairsDelegate;
	
	virtual FSupportingText GetSupportingText() override;

	virtual void OnComponentCreated() override;

	virtual void ApplyEffect() override;

	virtual void RemoveEffect() override;
	
};

