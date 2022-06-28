#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Resists,
	"UType.Combat.CombineModifiers.Coverage.Resists",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining (multi-Type) modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_Combat_CombineModifiers_Coverage_Resists::RunTest(const FString& Parameters)
{

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1, EAttackModifierMode::Coverage), 0.5F,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0, EAttackModifierMode::Coverage), 0.5F,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5, EAttackModifierMode::Coverage), 0.5F,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}