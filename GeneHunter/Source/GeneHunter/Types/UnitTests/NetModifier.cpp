#pragma once

#include "GeneHunter/FUnitTestUtilities.h"



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_NetModifier, "UType.NetModifier", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_NetModifier::RunTest(const FString& Parameters)
{
	GET_DUMMY_TYPES()
	
	if (Ground)
	{
		FString DeWater = "No";
		if (Water)
			DeWater = Water->GetName();
		TestEqual(
			"GetNetModifier (ineffective single attack vs dual defender) ::" + DeWater + "::",
			UType::GetNetModifier({Ground}, {Fighting, Bug}),
			0.5F,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Bug, Electric}),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Electric}),
			2,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (ineffective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Flying, Electric}, EAttackModifierMode::MultiType),
			0,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Bug, Grass}, EAttackModifierMode::MultiType),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Ground, Fighting}, EAttackModifierMode::MultiType),
			2,FUnitTestUtilities::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}

	return true;
}