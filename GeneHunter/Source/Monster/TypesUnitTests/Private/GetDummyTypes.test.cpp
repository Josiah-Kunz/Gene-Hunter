#pragma once

#include "TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_GetDummyTypes,
	"__GeneHunter.UType.GetDummyTypes",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Ensures the macro GET_DUMMY_TYPES() works.
 */
bool FUType_GetDummyTypes::RunTest(const FString& Parameters)
{

	// Import types
	GET_DUMMY_TYPES()
	constexpr uint8 ExpectedNumTypes = 12;

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