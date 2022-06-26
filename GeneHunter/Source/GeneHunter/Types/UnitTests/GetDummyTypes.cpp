#pragma once

#include "GeneHunter/FUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_GetDummyTypes, "UType.GetDummyTypes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Ensures the macro GET_DUMMY_TYPES() works.
 */
bool FUType_GetDummyTypes::RunTest(const FString& Parameters)
{

	// Import types
	GET_DUMMY_TYPES()

	// Number of assets
	TArray<FAssetData> TypeAssets;
	UDummyType::GetAllDummyAssets(TypeAssets);
	TestEqual(
				"GET_DUMMY_TYPES number of assets loaded",
				TypeAssets.Num(),
				12,FUnitTestUtilities::TOLERANCE);

	// Number of types
	TestEqual(
				"GET_DUMMY_TYPES number of array elements",
				AllDummyTypes.Num(),
				12,FUnitTestUtilities::TOLERANCE);


	// Non-null types
	TestNotNull("AllDummyTypes[0] non-null",
		AllDummyTypes[0]);
	
	// Done!
	return true;
}