#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Utilities_GetDummyTypes,
	"UType.Utilities.GetDummyTypes",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Ensures the macro GET_DUMMY_TYPES() works.
 */
bool FUType_Utilities_GetDummyTypes::RunTest(const FString& Parameters)
{

	// Import types
	GET_DUMMY_TYPES()

	// Number of assets
	TArray<FAssetData> TypeAssets;
	UDummyType::GetAllDummyAssets(TypeAssets);
	TestEqual(
				"GET_DUMMY_TYPES number of assets loaded",
				TypeAssets.Num(),
				12,FTypeUnitTestUtilities::TOLERANCE);

	// Number of types
	TestEqual(
				"GET_DUMMY_TYPES number of array elements",
				AllDummyTypes.Num(),
				12,FTypeUnitTestUtilities::TOLERANCE);


	// Non-null types
	TestNotNull("AllDummyTypes[0] non-null",
		AllDummyTypes[0]);
	
	// Done!
	return true;
}