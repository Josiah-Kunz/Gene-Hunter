#pragma once

#include "TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_Coverage_Heals,
	"__GeneHunter.UType.Combat.CombineModifiers.Coverage.Heals",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_Coverage_Heals::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2, EAttackModifierMode::Coverage), 2,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1, EAttackModifierMode::Coverage), 1,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5, EAttackModifierMode::Coverage), 0.5F,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0, EAttackModifierMode::Coverage), 0,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1, EAttackModifierMode::Coverage), -1,
		UTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}