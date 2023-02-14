#pragma once

#include "CoreMinimal.h"
#include "MutationComponent_BaseClass.h"
#include"CombatStat.h"
#include "CombatStatsComponent.h"
#include "CombatStatsComponent/Public/ModificationMode.h"
#include "CombatStatsComponent/Public/StatValueType.h"
#include "BerserkerGene.generated.h"

/**
 * +15% PhA | -10% PhD, SpD
 * A little boring, but sometimes it's best to have at least one boring, tried-and-true option.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UBerserkerGene : public UMutationComponent_BaseClass
{
	GENERATED_BODY()

	UBerserkerGene();
/* //TODO all this
#pragma region Public variables

public:

	// The thing to attach to
	// ----------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UCombatStatsComponent* StatsComponent;

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
	//todo UCombatStatsComponent::FRecalculateStatsDelegate Delegate;

#pragma endregion

	*/

#pragma region Overrides

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

	virtual FSupportingText GetSupportingText() override;

#pragma endregion
};

