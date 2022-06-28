﻿
#include <string>

#include "../Type.h"
#include "DummyType.h"
#include "GeneHunter/FTypeUnitTestUtilities.h"
#include "AITestSuite/Public/AITestsCommon.h"
#include "NavMesh/RecastNavMesh.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Analysis, "UType.MatchupAnalysis", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Analysis::RunTest(const FString& Parameters)
{
	
	/*
	
#pragma region Coverage Analyze test

	// Get the UTypes (actual)
	Actual = UType::AnalyzeVsSingle(
			{Ground, Flying},
			TArray<UType*>(AllDummyTypes),
			FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
				EAttackModifierMode::Coverage,
				true
			);

	// Perform the test
	bPass = FFUnitTestUtilities::TArrayAreEqual(Actual, {Electric, Fire, Poison, Rock, Steel, Bug, Fighting, Grass}, Desc);
	TestEqual(
		"Flying/Ground coverage attack " + Desc,
		bPass, true
	);
#pragma endregion

#pragma region AnalyzeAll tests

	// AnalyzeAll 1v1 attacking
	Actual = UType::AnalyzeAll(
		TArray<UType*>(AllDummyTypes),
		1, 1, 
		FFloatRange{
					FFloatRangeBound::Inclusive(1),
					FFloatRangeBound::Open()
					},
		true,
		EAttackModifierMode::Coverage
	);

	// Perform the test
	bPass = FFUnitTestUtilities::TArrayAreEqual(
		Actual,
		{Ice, Fire, Steel, Water},
		Desc);
	TestEqual(
		"AnalyzeAll 1v1 atk never resisted" + Desc,
		bPass, true
	);
	
	// AnalyzeAll 2v1 attacking
	Actual = UType::AnalyzeAll(
		TArray<UType*>(AllDummyTypes),
		2, 1, 
		FFloatRange{
					FFloatRangeBound::Exclusive(1),
					FFloatRangeBound::Open()
					},
					true,
					EAttackModifierMode::Coverage
	);

	// Perform the test
	// For the purposes of this test, Water and Ice have been made effective against EVERYTHING
	// (otherwise, the type combinations are too numerous to compute by hand)
	bPass = FFUnitTestUtilities::TArrayAreEqual(
		Actual,
		{
			// Water/Ice + all types
			Ice, Bug, Ice, Electric, Ice, Fighting, Ice, Fire, Ice, Flying, Ice, Grass, Ice, Ground, Ice, Poison, Ice, Rock, Ice, Steel, Ice, Water,
			Water, Bug, Water, Electric, Water, Fighting, Water, Fire, Water, Flying, Water, Grass, Water, Ground, Water, Poison, Water, Rock, Water, Steel,
			// Other "magic" combinations that complement each other
			//Flying, Ground,
			},
		Desc);
	TestEqual(
		"AnalyzeAll 2v1 atk always effective" + Desc,
		bPass, true
	);

	// AnalyzeAll 1v1 defending
    	Actual = UType::AnalyzeAll(
    		TArray<UType*>(AllDummyTypes),
    		1, 1, 
    		FFloatRange{
    					FFloatRangeBound::Open(),
    					FFloatRangeBound::Inclusive(1)
    					},
    					false,
					EAttackModifierMode::Coverage
    	);
    
    	// Perform the test
    	bPass = FFUnitTestUtilities::TArrayAreEqual(
    		Actual,
    		{},
    		Desc);
    	TestEqual(
    		"AnalyzeAll 1v1 def never weak" + Desc,
    		bPass, true
    	);
	
#pragma endregion

*/

#pragma region Sorting tests

	// TODO
	
#pragma endregion
	
	// All passed!
	return true;
}