#pragma once

#include "GeneHunter/FUnitTestUtilities.h"



IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_NetModifier, "UType.NetModifier", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_NetModifier::RunTest(const FString& Parameters)
{
	GET_DUMMY_TYPES()
	
	if (Ground)
	{
		TestEqual(
			"NetModifier (Ground vs. Fighting + Bug should be ineffective)",
			UType::GetNetModifier({Ground}, {Fighting, Bug},
				EAttackModifierMode::MultiType, true),
			0.5F,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Ground vs. Electric + Bug should be neutral)",
			UType::GetNetModifier({Ground}, {Bug, Electric},
				EAttackModifierMode::MultiType, true),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Ground vs. Fighting + Electric should be effective)",
			UType::GetNetModifier({Ground}, {Fighting, Electric},
				EAttackModifierMode::MultiType, true),
			2,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Flying + Electric should be ineffective)",
			UType::GetNetModifier({Flying, Ground}, {Flying, Electric},
				EAttackModifierMode::MultiType, true),
			0,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Bug + Grass should be neutral)",
			UType::GetNetModifier({Flying, Ground}, {Bug, Grass},
				EAttackModifierMode::MultiType, true),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Ground + Fighting should be effective)",
			UType::GetNetModifier({Flying, Ground}, {Ground, Fighting},
				EAttackModifierMode::MultiType, true),
			2,FUnitTestUtilities::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}

	return true;
}