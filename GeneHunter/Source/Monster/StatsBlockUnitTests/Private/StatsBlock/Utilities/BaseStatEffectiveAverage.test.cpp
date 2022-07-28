#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Utilities_BaseStatEffectiveAverage,
	"FStat.StatsBlock.Utilities.Base Stat Effective Average",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Utilities_BaseStatEffectiveAverage::RunTest(const FString& Parameters)
{
	
	// Test
	DUMMY_BASE_STATS_BLOCK
	const float EffectiveAverage = StatsBlock->BaseStatEffectiveAverage();
	const float Expected = 96;
	TestTrue(FString::Printf(TEXT("Base Stat effective average: %s vs %s"),
		*FString::SanitizeFloat(EffectiveAverage),
		*FString::SanitizeFloat(Expected)),
	FMathf::Abs(EffectiveAverage - Expected) < UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	return true;
}