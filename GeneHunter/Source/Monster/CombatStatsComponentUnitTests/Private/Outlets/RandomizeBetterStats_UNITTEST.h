// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"
#include "EffectComponent.h"
#include "Outlets/RandomizeStatsOutlet.h"

#include "RandomizeBetterStats_UNITTEST.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class COMBATSTATSCOMPONENTUNITTESTS_API URandomizeBetterStats_UNITTEST : public UEffectComponent
{
	GENERATED_BODY()

public:

	const int32 MinBaseStat = 75;
	const int32 MinBasePairs = 90;

	UPROPERTY()
	UCombatStatsComponent* StatsComponent;

	UPROPERTY()
	FBeforeRandomizeStatsDelegate Delegate;

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
		BIND_DELEGATE(Delegate, URandomizeBetterStats_UNITTEST::BetterRandomStats);

		// Add it
		StatsComponent->RandomizeStatsOutlet.AddBefore(Delegate);
	}

	UFUNCTION()
	void BetterRandomStats(const EStatEnum TargetStat, const FStatRandParams OriginalParams,
		FStatRandParams& ParamsToBeUsed)
	{
		ParamsToBeUsed.MinBaseStat = MinBaseStat;
		ParamsToBeUsed.MinBasePairs = MinBasePairs;
	}

	

};
