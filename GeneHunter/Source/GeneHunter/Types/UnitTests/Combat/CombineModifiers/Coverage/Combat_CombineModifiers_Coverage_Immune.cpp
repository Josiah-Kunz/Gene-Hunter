#pragma once

#include "GeneHunter/Types/UnitTests/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Immune,
	"UType.Combat.CombineModifiers.Coverage.Immune",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_Coverage_Immune::RunTest(const FString& Parameters)
{

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1, EAttackModifierMode::Coverage), 0,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0, EAttackModifierMode::Coverage), 0,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5, EAttackModifierMode::Coverage), 0.5F,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1, EAttackModifierMode::Coverage), 1,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2, EAttackModifierMode::Coverage), 2,
		UTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}