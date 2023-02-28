#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "CombatStatsComponent/Public/ModificationMode.h"
#include "CombatStatsComponent/Public/StatValueType.h"
#include "Invulnerable.generated.h"

/**
 * Base class for avoiding damage. Has a priority of 100 (high).
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class BUFFCOMPONENT_API UInvulnerable : public UBuffComponent
{
	GENERATED_BODY()

#pragma region Public variables

public:

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

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual float StartingDuration() override;

	virtual float GetPriority() override;

#pragma endregion

#pragma region Private functions

	UFUNCTION()
	void DontTakeDamage(const EStatEnum TargetStat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OriginalValue, float& AttemptedValue);

#pragma endregion
	
};

