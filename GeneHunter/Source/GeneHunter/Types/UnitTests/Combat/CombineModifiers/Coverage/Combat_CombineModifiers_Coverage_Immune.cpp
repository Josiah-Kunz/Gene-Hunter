#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Immune,
	"UType.Combat.CombineModifiers.Coverage.Immune",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_Coverage_Immune::RunTest(const FString& Parameters)
{

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1, EAttackModifierMode::Coverage), 0,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0, EAttackModifierMode::Coverage), 0,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5, EAttackModifierMode::Coverage), 0.5F,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}