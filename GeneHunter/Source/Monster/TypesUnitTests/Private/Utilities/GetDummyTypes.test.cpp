#pragma once

#include "Utilities/TypeUnitTestUtilities.h"
#include "DummyType.h"

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
				12,UTypeUnitTestUtilities::TOLERANCE);

	// Number of types
	TestEqual(
				"GET_DUMMY_TYPES number of array elements",
				AllDummyTypes.Num(),
				12,UTypeUnitTestUtilities::TOLERANCE);


	// Non-null types
	TestNotNull("AllDummyTypes[0] non-null",
		AllDummyTypes[0]);

	// Destroy world + dummy types
	GC_DUMMY_TYPES()
	
	// Done!
	return true;
}