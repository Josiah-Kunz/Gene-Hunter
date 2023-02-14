#pragma once

#include "CoreMinimal.h"
#include "BuffComponent_BaseClass.h"
#include"CombatStat.h"
#include "CombatStatsComponent.h"
#include "CombatStatsComponent/Public/ModificationMode.h"
#include "CombatStatsComponent/Public/StatValueType.h"
#include "DimensionalShift.generated.h"

/**
 * +15% PhA | -10% PhD, SpD
 * A little boring, but sometimes it's best to have at least one boring, tried-and-true option.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDimensionalShift : public UBuffComponent_BaseClass
{
	GENERATED_BODY()

#pragma region Public variables

public:

	// The thing to attach to
	// ----------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

	// Delegation variables
	// --------------------
	
	std::function<void(EStatEnum, float&, const EStatValueType, const EModificationMode)> Lambda =
		[this](const EStatEnum InStat, float& InValue, const EStatValueType InValueType, const EModificationMode InMode)
	{
		if (InStat == EStatEnum::Health)
			StatsComponent->AvertReduction(InStat, InValue, InValueType, InMode);
	};
	//todo UCombatStatsComponent::FModifyStatDelegate Delegate;

#pragma endregion

#pragma region Overrides

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual float StartingDuration() override;

#pragma endregion
};

