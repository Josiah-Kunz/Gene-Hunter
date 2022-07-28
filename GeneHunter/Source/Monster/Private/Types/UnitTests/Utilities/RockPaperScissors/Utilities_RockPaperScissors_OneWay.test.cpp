#pragma once

#include "UnitTests/Utilities/TypeUnitTestUtilities.h"
#include "UnitTests/DummyType.h"

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

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success
	// Note: for the dummy Types, not all dis/advantages are coded, but this one specifically is!
	const TArray<FTypeArray1D*> Expected = {
		new FTypeArray1D{{Flying, Grass, Rock}},
		new FTypeArray1D{{Flying, Fighting, Rock}}	// 2-way still counts!
	};

	// Get actual
	TArray<FTypeArray1D*> Actual;
	UTypeUnitTestUtilities::GetRockPaperScissors(AllTypes, false, Actual);
		
	// Do the test
	FString Desc = "";
	bool bPass = FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Actual, Expected, Desc);
	TestEqual(
	"Rock-Paper-Scissors (1-Way) " + Desc,
	bPass, true
	);
	return true;
	
}