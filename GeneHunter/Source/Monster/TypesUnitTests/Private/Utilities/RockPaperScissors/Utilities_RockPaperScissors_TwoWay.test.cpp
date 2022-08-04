#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Utilities_RockPaperScissors_TwoWay,
	"GeneHunter.UType.Utilities.Rock-Paper-Scissors.2-Way",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests for "rock-paper-scissors" Type triads (2-way), such as Pokemon's Fire > Grass > Water.
 */
bool FUType_Utilities_RockPaperScissors_TwoWay::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Define success
	// Note: for the dummy Types, not all dis/advantages are coded, but this one specifically is!
	const TArray<FTypeArray1D> Expected = {
		FTypeArray1D{{Flying, Fighting, Rock}}
	};

	// Get actual
	TArray<FTypeArray1D> Actual;
	UTypeUnitTestUtilities::GetRockPaperScissors(AllDummyTypes, true, Actual);
		
	// Do the test
	FString Desc = "";
	bool bPass = FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Actual, Expected, Desc);
	TestEqual(
	"Rock-Paper-Scissors (2-Way) " + Desc,
	bPass, true
	);

	
	
	
	return true;
	
}