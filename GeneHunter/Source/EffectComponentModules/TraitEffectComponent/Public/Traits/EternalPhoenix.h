#pragma once

#include "CombatStatsComponent.h"
#include "CoreMinimal.h"
#include "TraitEffectComponent.h"
#include "Outlets/ModifyStatOutlet.h"

#include "EternalPhoenix.generated.h"

/**
 * When killed, heal to full health instead. Useful for things like training dummies.
 */
UCLASS(ClassGroup=(Effects, Traits), meta=(BlueprintSpawnableComponent))
class TRAITEFFECTCOMPONENT_API UEternalPhoenix : public UTraitEffectComponent
{
	GENERATED_BODY()
	
public:

	/**
	 * Since the primary goal of this effect is to save us from dying, we'll need this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * This is the delegate that attaches to UCombatStatComponent's BeforeModifyStat Outlet.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Outlets", meta = (AllowPrivateAccess = "true"))
	FBeforeModifyStatDelegate ModifyStatOutlet;
	
	virtual FSupportingText GetSupportingText() override;

	virtual void OnComponentCreated() override;

	virtual void ApplyEffect() override;

	virtual void RemoveEffect() override;

	virtual float GetPriority() override;

private:

	UFUNCTION()
	void HealToFull(const EStatEnum TargetStat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OriginalValue, float& AttemptedValue);
	
};

