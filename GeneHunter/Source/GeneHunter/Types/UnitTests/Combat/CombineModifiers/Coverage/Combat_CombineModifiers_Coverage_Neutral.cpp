#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Neutral,
	"UType.Combat.CombineModifiers.Coverage.Neutral",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_Coverage_Neutral::RunTest(const FString& Parameters)
{

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1, EAttackModifierMode::Coverage), 1,
		FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2, EAttackModifierMode::Coverage), 2,
		FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}