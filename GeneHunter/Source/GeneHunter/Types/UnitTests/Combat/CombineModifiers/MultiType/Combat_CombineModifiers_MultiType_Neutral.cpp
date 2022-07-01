﻿#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_CombineModifiers_MultiType_Neutral,
	"UType.Combat.CombineModifiers.MultiType.Neutral",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining (multi-Type) modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_Combat_CombineModifiers_MultiType_Neutral::RunTest(const FString& Parameters)
{

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1,FTypeUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2,FTypeUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}