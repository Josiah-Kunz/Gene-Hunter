/**
 * Tests an "Adamant nature" (a la Pokemon): +10% PhA | -10% SpA
 */

#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEffects_Delegates_RecalculateStats,
	"__GeneHunter.Effects.Delegate Tests.Recalculate Stats (\"Adamant\")",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FEffects_Delegates_RecalculateStats::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get baseline
	StatsComponent->RecalculateStats(true);
	const float OriginalPhA = StatsComponent->PhysicalAttack.GetCurrentValue();
	const float OriginalSpA = StatsComponent->SpecialAttack.GetCurrentValue();
	
	// Define "adamant" delegate (+10% PhA/-10% SpA)
	UStatsComponent::FRecalculateStatDelegate AdamantRecalculateDelegate;
	AdamantRecalculateDelegate.BindLambda([StatsComponent](FStat* Stat, bool bResetCurrent)
	{

		// +10% PhA
		if ( Stat->Name() == StatsComponent->PhysicalAttack.Name())
		{
			Stat->ModifyValue(10, EStatValueType::Permanent, EModificationMode::AddPercentage);
			if (bResetCurrent)
				Stat->ModifyValue(10, EStatValueType::Current, EModificationMode::AddPercentage);
		}

		// -10% SpA
		if ( Stat->Name() == StatsComponent->SpecialAttack.Name())
		{
			Stat->ModifyValue(-10, EStatValueType::Permanent, EModificationMode::AddPercentage);
			if (bResetCurrent)
				Stat->ModifyValue(-10, EStatValueType::Current, EModificationMode::AddPercentage);
		}
			
	});
	StatsComponent->AfterRecalculateStatsArray.Add(AdamantRecalculateDelegate);

	// Recalculate stats
	StatsComponent->RecalculateStats(true);

	// Check PhA
	const float ExpectedPhA = OriginalPhA * 1.1f;
	TestTrue(FString::Printf(TEXT("Increase PhA by 10 percent?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedPhA),
		*FString::SanitizeFloat(StatsComponent->PhysicalAttack.GetCurrentValue())),
	FMathf::Abs(ExpectedPhA - StatsComponent->PhysicalAttack.GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);

	// Check SpA
	const float ExpectedSpA = OriginalSpA * 0.9f;
	TestTrue(FString::Printf(TEXT("Decrease SpA by 10 percent?: Original [%s] | Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(OriginalSpA),
		*FString::SanitizeFloat(ExpectedSpA),
		*FString::SanitizeFloat(StatsComponent->SpecialAttack.GetCurrentValue())),
	FMathf::Abs(ExpectedSpA - StatsComponent->SpecialAttack.GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}