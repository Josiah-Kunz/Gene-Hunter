#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "CombatStatUnitTestUtilities.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsComponent_Utilities_BaseStatTotal,
	"__GeneHunter.FStat.StatsComponent.Utilities.Base Stat Total",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsComponent_Utilities_BaseStatTotal::RunTest(const FString& Parameters)
{
	
	// Test
	DUMMY_BASE_STATS_BLOCK
	const float BST = StatsComponent->BaseStatTotal();
	constexpr float Expected = 636;
	TestTrue(FString::Printf(TEXT("Base Stat total: %s vs %s"),
		*FString::SanitizeFloat(BST),
		*FString::SanitizeFloat(Expected)),
	FMathf::Abs(BST - Expected) < UStatUnitTestUtilities::TOLERANCE);
	BASESTATS_GC
	
	// Return
	return true;
}