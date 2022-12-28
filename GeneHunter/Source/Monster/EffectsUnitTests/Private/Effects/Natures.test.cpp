/**
 * Tests "natures" (a la Pokemon): +10% | -10% or neutral natures.
 */

#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 
#include "Effects/Public/Effects/StatModifier.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEffects_Effects_Natures,
                                 "__GeneHunter.Effects.Effect Tests.\"Natures\"",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FEffects_Effects_Natures::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Loop over 
	for(int i=0; i<StatsComponent->StatsArray.Num(); i++)
	{
		FStatModifier StatModifier{StatsComponent};
	}
	
	// Get baseline
	

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