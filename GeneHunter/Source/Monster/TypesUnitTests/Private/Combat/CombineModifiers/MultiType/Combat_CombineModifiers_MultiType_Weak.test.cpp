#pragma once
#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_MultiType_Weak,
	"GeneHunter.UType.Combat.CombineModifiers.MultiType.Weak",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining (multi-Type) modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_Combat_CombineModifiers_MultiType_Weak::RunTest(const FString& Parameters)
{
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F,UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0,UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1,UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2,UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4,UTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}