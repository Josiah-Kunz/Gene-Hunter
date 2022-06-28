#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_MultiType_Resists,
	"UType.Combat.CombineModifiers.MultiType.Resists",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining (multi-Type) modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_Combat_CombineModifiers_MultiType_Resists::RunTest(const FString& Parameters)
{

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1,FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}