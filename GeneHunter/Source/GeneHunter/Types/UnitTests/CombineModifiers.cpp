#pragma once

#include "GeneHunter/FUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_CombineModifiers, "UType.CombineModifiers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining (multi-Type) modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_CombineModifiers::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2), -0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1), -1,FUnitTestUtilities::TOLERANCE);

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2), 0,FUnitTestUtilities::TOLERANCE);

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1,FUnitTestUtilities::TOLERANCE);

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2,FUnitTestUtilities::TOLERANCE);
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4,FUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}