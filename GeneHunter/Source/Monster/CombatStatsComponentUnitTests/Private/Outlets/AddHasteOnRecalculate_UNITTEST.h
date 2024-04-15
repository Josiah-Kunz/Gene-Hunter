// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/RecalculateStatsOutlet.h"

#include "AddHasteOnRecalculate_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMBATSTATSCOMPONENTUNITTESTS_API UAddHasteOnRecalculate_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	const float HasteIncrease = 200;

	UPROPERTY()
	UCombatStatsComponent* StatsComponent;

	UPROPERTY()
	FBeforeRecalculateStatsDelegate Delegate;

	virtual void OnComponentCreated() override
	{
		// Get StatsComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

		// Guard
		if (StatsComponent == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("No UStatsComponent found!"
			" This is required for the Haste unit test."))
			DestroyComponent();
			return;
		}

		// Soopah doopah
		Super::OnComponentCreated();
		
		// Bind the delegate
		BIND_DELEGATE(Delegate, UAddHasteOnRecalculate_UNITTEST::IncreaseHaste);

		// Add it
		StatsComponent->RecalculateStatsOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void IncreaseHaste(const EStatEnum TargetStat, const bool bResetCurrent,
		const float OriginalCurrent, const float OriginalPermanent)
	{
		if (ShouldApplyEffect() && TargetStat == EStatEnum::Haste)
		{
			StatsComponent->ModifyStat(EStatEnum::Haste, OriginalCurrent + HasteIncrease, EStatValueType::Current,
				EModificationMode::AddAbsolute);
		}
	}

	

};
