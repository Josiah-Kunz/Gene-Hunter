#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "NegativeAuraComponent.h"
#include "Outlets/ModifyStatOutlet.h"
#include "WoundedSoul.generated.h"

/**
 * -75% healing
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class NEGATIVEAURACOMPONENT_API UWoundedSoul : public UNegativeAuraComponent
{
	GENERATED_BODY()

	UWoundedSoul();

#pragma region Static (public) variables

public:

	/**
	 * Percent reduction to all healing.
	 */
	inline static constexpr float HealingReduction = 25;

#pragma endregion

#pragma region Public variables

public:

	/**
	 * Since the primary goal of this effect is to modify stats, we'll need this.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	/**
	 * This is the delegate that attaches to UCombatStatComponent's BeforeModifyStat Outlet.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBeforeModifyStatDelegate Delegate;

	/**
	 * This is the function that binds to the aforementioned Delegate.
	 */
	UFUNCTION(BlueprintCallable)
	void BeforeModifyStats(const EStatEnum TargetStat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OriginalValue, float& AttemptedValue);

#pragma endregion

#pragma region Overrides

public:

	virtual void InitializeEffect() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

#pragma endregion
	
};

