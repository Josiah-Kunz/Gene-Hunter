#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_GetDummyTypes,
	"UType.GetDummyTypes",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Ensures the macro GET_DUMMY_TYPES() works.
 */
bool FUType_GetDummyTypes::RunTest(const FString& Parameters)
{

	// Import types
	GET_DUMMY_TYPES()
	constexpr int ExpectedNumTypes = 12;

	// Number of types
	TestEqual(
				"GET_DUMMY_TYPES number of array elements",
				AllDummyTypes.Num(),
				ExpectedNumTypes,UTypeUnitTestUtilities::TOLERANCE);


	// Non-null types
	if (AllDummyTypes.Num() == ExpectedNumTypes)
		for(const UType* Type : AllDummyTypes)
			TestNotNull("AllDummyTypes[0] non-null", Type);

	
	
	
	// Done!
	return true;
}