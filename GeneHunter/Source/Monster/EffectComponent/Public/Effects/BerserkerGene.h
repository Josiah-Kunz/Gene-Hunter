#pragma once

#include "CoreMinimal.h"
#include "MutationComponent.h"
#include "Stat.h"
#include "StatsComponent.h"
#include "StatsComponent/Public/ModificationMode.h"
#include "StatsComponent/Public/StatValueType.h"
#include "BerserkerGene.generated.h"

/**
 * +15% PhA | -10% PhD, SpD
 * A little boring, but sometimes it's best to have at least one boring, tried-and-true option.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UBerserkerGene : public UMutationComponent
{
	GENERATED_BODY()

	UBerserkerGene();

#pragma region Public variables

public:

	// The thing to attach to
	// ----------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;

	// Delegation variables
	// --------------------
	
	std::function<void(EStatEnum, const bool)> Lambda = [this](EStatEnum InStat, const bool bResetCurrent)
	{
		switch(InStat)
		{
		case EStatEnum::PhysicalAttack:
				StatsComponent->GetStat(InStat).ModifyValue(15, EStatValueType::Permanent, EModificationMode::AddPercentage);
				if (bResetCurrent)
					StatsComponent->GetStat(InStat).ModifyValue(15, EStatValueType::Current, EModificationMode::AddPercentage);
			break;
		case EStatEnum::PhysicalDefense: case EStatEnum::SpecialDefense:
				StatsComponent->GetStat(InStat).ModifyValue(-10, EStatValueType::Permanent, EModificationMode::AddPercentage);
				if (bResetCurrent)
					StatsComponent->GetStat(InStat).ModifyValue(-10, EStatValueType::Current, EModificationMode::AddPercentage);
			break;
		default:
			break;
		}
	};
	UStatsComponent::FRecalculateStatsDelegate Delegate;

#pragma endregion

#pragma region Overrides

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

#pragma endregion
};

