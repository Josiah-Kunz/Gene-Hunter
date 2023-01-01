#pragma once

#include "CoreMinimal.h"
#include "BuffComponent.h"
#include "Stat.h"
#include "StatsComponent.h"
#include "StatsComponent/Public/ModificationMode.h"
#include "StatsComponent/Public/StatValueType.h"
#include "DimensionalShift.generated.h"

/**
 * +15% PhA | -10% PhD, SpD
 * A little boring, but sometimes it's best to have at least one boring, tried-and-true option.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UDimensionalShift : public UBuffComponent
{
	GENERATED_BODY()

#pragma region Public variables

public:

	// The thing to attach to
	// ----------------------
	
	

	// Delegation variables
	// --------------------
	
	std::function<void(FStat*, float&, const EStatValueType, const EModificationMode)> Lambda =
		[this](FStat* InStat, float& InValue, const EStatValueType InValueType, const EModificationMode InMode)
	{
		if (InStat->Name().Equals(StatsComponent->Health.Name()))
			UStatsComponent::AvertReduction(InStat, InValue, InValueType, InMode);
	};
	UStatsComponent::FModifyStatDelegate Delegate;

#pragma endregion

#pragma region Overrides

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

	virtual float StartingDuration() override;

#pragma endregion
};

