#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "Stat.h"
#include "StatsComponent.h"
#include "StatsComponent/Public/ModificationMode.h"
#include "StatsComponent/Public/StatValueType.h"
#include "StatModifierTrigger.h"
#include "StatModifier.generated.h"

/**
 * An FEffect that can modify a single stat on either UStatsComponent::RecalculateStats, UStatsComponent::ModifyStats,
 *	or both.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UStatModifier : public UEffectComponent
{
	GENERATED_BODY()

#pragma region Public variables

public:

	// The thing to attach to
	// ----------------------
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	UStatsComponent* StatsComponent;

	// How to modify
	// -------------
	
	FStat* Stat;
	
	float Value;
	EModificationMode Mode;
	EStatValueType ValueType;
	
	EStatModifierTrigger Trigger = EStatModifierTrigger::RecalculateStats;

	// Delegation variables
	// --------------------
	
	std::function<void(FStat*, const bool)> RecalculateLambda = [this](FStat* InStat, const bool bResetCurrent)
	{
		if (InStat->Name().Equals(Stat->Name()))
			InStat->ModifyValue(Value, ValueType, Mode);
	};
	UStatsComponent::FRecalculateStatsDelegate RecalculateStatsDelegate;

	std::function<void(FStat*, const float, const EStatValueType, const EModificationMode)> ModifyLambda =
		[this](FStat* InStat, const float InValue, const EStatValueType InValueType, const EModificationMode InMode)
		{
			if (InStat->Name().Equals(Stat->Name()))
				InStat->ModifyValue(Value, ValueType, Mode);
		};
	UStatsComponent::FModifyStatDelegate ModifyStatDelegate;

#pragma endregion

#pragma region Overrides

	virtual void OnComponentCreated() override;

	virtual void OnComponentDestroyed(bool bDestroyingHierarchy) override;

#pragma endregion
};

