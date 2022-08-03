#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_MultiType_Heals,
	"UType.Combat.CombineModifiers.MultiType.Heals",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_CombineModifiers_MultiType_Heals::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2, EAttackModifierMode::MultiType), -0.5F,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1, EAttackModifierMode::MultiType), -1,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5, EAttackModifierMode::MultiType), -1,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0, EAttackModifierMode::MultiType), -1,
		UTypeUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1, EAttackModifierMode::MultiType), -1,
		UTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}