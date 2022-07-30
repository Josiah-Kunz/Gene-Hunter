#pragma once

#include "Utilities/TypeUnitTestUtilities.h"
#include "DummyType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Utilities_RockPaperScissors_OneWay,
	"UType.Utilities.Rock-Paper-Scissors.1-Way",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests for "rock-paper-scissors" Type triads (1-way), such as Pokemon's Fire > Grass > Water.
 */
bool FUType_Utilities_RockPaperScissors_OneWay::RunTest(const FString& Parameters)
{
	
	// Get all types
	GET_DUMMY_TYPES()

	// Define success
	// Note: for the dummy Types, not all dis/advantages are coded, but this one specifically is!
	const TArray<FTypeArray1D*> Expected = {
		new FTypeArray1D{{Flying, Grass, Rock}},
		new FTypeArray1D{{Flying, Fighting, Rock}}	// 2-way still counts!
	};

	// Get actual
	TArray<FTypeArray1D*> Actual;
	UTypeUnitTestUtilities::GetRockPaperScissors(AllDummyTypes, false, Actual);
		
	// Do the test
	FString Desc = "";
	bool bPass = FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Actual, Expected, Desc);
	TestEqual(
	"Rock-Paper-Scissors (1-Way) " + Desc,
	bPass, true
	);

	// Destroy tmp world and collect its garbage
	GC_DUMMY_TYPES()

	// Return
	return true;
	
}