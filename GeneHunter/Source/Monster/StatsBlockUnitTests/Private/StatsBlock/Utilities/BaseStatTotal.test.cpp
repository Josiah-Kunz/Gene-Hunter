﻿#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Utilities_BaseStatTotal,
	"FStat.StatsBlock.Utilities.Base Stat Total",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Utilities_BaseStatTotal::RunTest(const FString& Parameters)
{
	
	// Test
	DUMMY_BASE_STATS_BLOCK
	const float BST = StatsBlock->BaseStatTotal();
	const float Expected = 636;
	TestTrue(FString::Printf(TEXT("Base Stat total: %s vs %s"),
		*FString::SanitizeFloat(BST),
		*FString::SanitizeFloat(Expected)),
	FMathf::Abs(BST - Expected) < UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	return true;
}