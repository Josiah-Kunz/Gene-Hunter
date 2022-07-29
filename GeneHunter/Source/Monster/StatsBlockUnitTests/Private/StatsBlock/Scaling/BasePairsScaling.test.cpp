#pragma once

#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Scaling_BasePairsScaling,
	"UStat.StatsBlock.Scaling.Base Pairs Scaling",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Scaling_BasePairsScaling::RunTest(const FString& Parameters)
{

	// Most of these values will be in the millions, and this tolerance is consistent with the documentation
	//	(specifically, Figure 2 about Attack vs. #BasePairs).
	const float Tolerance = 0.1e6;
	
	// Set up
	FPhysicalAttack PhA = {};
	PhA.BaseStat = 100;
	const int Level = 100;

	// Map of <#BasePairs, ExpectedValue>
	TMap<int, float> ExpectedValues = {
		{1, 4e6},
		{50, 10.2e6},
		{70, 11e6},
		{80, 11.5e6},
		{90, 11.8e6},
		{95, 11.9e6},
		{100, 12.1e6}
	};

	// Do the tests
	for(const TPair<int, float>& ExpectedValue : ExpectedValues)
	{
		PhA.BasePairs = ExpectedValue.Key;
		PhA.Update(Level);
		TestEqual(FString::Printf(TEXT("Physical Attack: %s BasePairs"), *FString::FromInt(ExpectedValue.Key)),
			PhA.GetCurrentValue(), ExpectedValue.Value, Tolerance);
	}
	
	// Return
	return true;
}