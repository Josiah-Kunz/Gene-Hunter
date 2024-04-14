
#pragma once

#include "ComponentUtilities.h"
#include "CombatStatUnitTestUtilities.h"
#include "MathUtil.h"
#include "NaturalSelector.h"

#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_NaturalSelector,
	"__GeneHunter.Effects.Component Tests.Natural Selector",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_NaturalSelector::RunTest(const FString& Parameters)
{
	
	// Get dummy + data
	const float BPThreshold = UNaturalSelector::MinBasePairs;
	DUMMY_BASE_STATS_BLOCK
	const TArray<EStatEnum> AllStats = StatsComponent->StatsArray;

	// These stats will be below the threshold
	const float DeficientValue = BPThreshold/2;
	const float AdequateValue = BPThreshold + (100-BPThreshold)/2;
	const TArray<EStatEnum> DeficientStats = {
		EStatEnum::Health,
		EStatEnum::Haste,
		EStatEnum::PhysicalDefense
	};

	// Set originals
	TMap<EStatEnum, float> OGBPs = {};
	for(const EStatEnum Stat : AllStats)
	{

		// Set BP
		if (DeficientStats.Contains(Stat))
		{
			StatsComponent->ModifyStat(Stat, DeficientValue, EStatValueType::BasePairs,
				EModificationMode::SetDirectly);
		} else
		{
			StatsComponent->ModifyStat(Stat, AdequateValue, EStatValueType::BasePairs,
				EModificationMode::SetDirectly);
		}

		// Add to array
		OGBPs.Add(Stat, StatsComponent->GetStat(Stat).BasePairs);
	}

	// Add the effect and see if it did anything
	ADD_NEW_COMPONENT(UNaturalSelector, NaturalSelector, DummyActor)
	bool bStillDeficient = false;
	for(const EStatEnum DeficientStat : DeficientStats)
	{
		if (StatsComponent->GetStat(DeficientStat).BasePairs < BPThreshold)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stat [%s] is still deficient!"),
				*UEnum::GetValueAsString(DeficientStat)
			)
			bStillDeficient = true;
		}
	}
	if (bStillDeficient)
	{
		return false;
	}

	// Randomize stats and make sure *all* aren't deficient
	// Do it 10 times to make sure we're not just lucky
	bool bRandSuccess = true;
	for(int i=0; i<10; i++)
	{
		StatsComponent->RandomizeBasePairs();
		for(const EStatEnum Stat : AllStats)
		{
			if (StatsComponent->GetStat(Stat).BasePairs < BPThreshold)
			{
				UE_LOG(LogTemp, Warning, TEXT("Randomizing base pairs failed on stat [%s]!"),
					*UEnum::GetValueAsString(Stat)
				)
				bRandSuccess = false;
			}
		}
	}
	if (!bRandSuccess)
	{
		return false;
	}

	// Take the effect off and see that we have the OG values
	NaturalSelector->DestroyComponent();
	bool bStatReset = true;
	for(const EStatEnum Stat : DeficientStats)
	{
		if (FMathf::Abs(OGBPs[Stat] - StatsComponent->GetStat(Stat).BasePairs) > 0.1f)
		{
			UE_LOG(LogTemp, Warning, TEXT("Stat [%s] did not reset when NaturalSelector was taken off!"),
				*UEnum::GetValueAsString(Stat)
			)
			bStatReset = false;
		}
	}
	if (!bStatReset)
	{
		return false;
	}
	 
	// Return
	BASESTATS_GC
	return true;
}