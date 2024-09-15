#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "CombatStatsComponent/Public/ModificationMode.h"
#include "CombatStatsComponent/Public/StatValueType.h"
#include "DebuffComponent.h"
#include "Outlets/ModifyStatOutlet.h"

#include "BrokenSoul.generated.h"

/**
 * Reduces healing by a large amount.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class DEBUFFCOMPONENT_API UBrokenSoul : public UDebuffComponent
{
	GENERATED_BODY()

#pragma region Public variables

public:

	/**
	 * Percent reduction to all healing.
	 */
	inline static constexpr float HealingReduction = 50;

	/**
	 * The thing to attach to.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* Stats;

	/**
	 * The delegate that does the work.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FBeforeModifyStatDelegate Delegate;

#pragma endregion

#pragma region Overrides

	virtual void InitializeEffect() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual float StartingDuration() override;

	virtual float GetPriority() override;

#pragma endregion

#pragma region Private functions

	UFUNCTION()
	void ReduceHealing(const EStatEnum TargetStat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OriginalValue, float& AttemptedValue);

#pragma endregion
	
};

