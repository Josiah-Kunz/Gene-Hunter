// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/ModifyStatOutlet.h"

#include "SoftenTheBlow_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMBATSTATSCOMPONENTUNITTESTS_API USoftenTheBlow_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	const EStatEnum SoftenStat = EStatEnum::PhysicalAttack;
	const float SoftenAmount = 0.9f;

	UPROPERTY()
	UCombatStatsComponent* StatsComponent;

	UPROPERTY()
	FBeforeModifyStatDelegate Delegate;

	virtual void OnComponentCreated() override
	{
		// Get StatsComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

		// Guard
		if (StatsComponent == nullptr)
		{
			return;
		}

		// Soopah doopah
		Super::OnComponentCreated();
		
		// Bind the delegate
		BIND_DELEGATE(Delegate, USoftenTheBlow_UNITTEST::SoftenStatLoss);

		// Add it
		StatsComponent->ModifyStatOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void SoftenStatLoss(const EStatEnum TargetStat, const EStatValueType ValueType, const EModificationMode Mode,
		const float OriginalValue, float& AttemptedValue)
	{
		if (ShouldApplyEffect() && TargetStat == SoftenStat)
		{
			const float OriginalStat = StatsComponent->GetStat(TargetStat).GetValue(ValueType);
			const float ModifiedStat = StatsComponent->GetModifiedValue(TargetStat, AttemptedValue, ValueType, Mode);
			if (ModifiedStat < OriginalStat)
			{
				AttemptedValue *= SoftenAmount;
			}
		}
	}

	

};
