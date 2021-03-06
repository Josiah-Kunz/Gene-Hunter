#pragma once

#include "GeneHunter/Types/UnitTests/Utilities/TypeUnitTestUtilities.h"
#include "GeneHunter/Types/UnitTests/DummyType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Utilities_RockPaperScissors_TwoWay,
	"UType.Utilities.Rock-Paper-Scissors.2-Way",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests for "rock-paper-scissors" Type triads (2-way), such as Pokemon's Fire > Grass > Water.
 */
bool FUType_Utilities_RockPaperScissors_TwoWay::RunTest(const FString& Parameters)
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
		new FTypeArray1D{{Flying, Fighting, Rock}}
	};

	// Get actual
	TArray<FTypeArray1D*> Actual;
	UTypeUnitTestUtilities::GetRockPaperScissors(AllTypes, true, Actual);
		
	// Do the test
	FString Desc = "";
	bool bPass = FTypeArray1D::ArrayOfTypeArray1DsAreEqual(Actual, Expected, Desc);
	TestEqual(
	"Rock-Paper-Scissors (2-Way) " + Desc,
	bPass, true
	);
	return true;
	
}