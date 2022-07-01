#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Weak,
	"UType.Combat.CombineModifiers.Coverage.Weak",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_Coverage_Weak::RunTest(const FString& Parameters)
{
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}