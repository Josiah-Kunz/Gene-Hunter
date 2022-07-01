/*
 * Tests {Atk} vs {Def}. Similar to, e.g., Combat_Attack_Coverage_DualDefender, but less exhaustive.
 *	That is, this tests static combinations (such as exactly {Fighting, But}) and Combat_Attack_Coverage_DualDefender
 *	tests against _all_ dummy Types.
 */

#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_NetModifier,
	"UType.Combat.CombineModifiers.NetModifier",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUType_Combat_NetModifier::RunTest(const FString& Parameters)
{
	GET_DUMMY_TYPES()
	
	if (Ground)
	{
		TestEqual(
			"NetModifier (Ground vs. Fighting + Bug should be ineffective)",
			UType::GetNetModifier({Ground}, {Fighting, Bug},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			0.5F,FTypeUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Ground vs. Electric + Bug should be neutral)",
			UType::GetNetModifier({Ground}, {Bug, Electric},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			1,FTypeUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Ground vs. Fighting + Electric should be effective)",
			UType::GetNetModifier({Ground}, {Fighting, Electric},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			2,FTypeUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Flying + Electric should be ineffective)",
			UType::GetNetModifier({Flying, Ground}, {Flying, Electric},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			0,FTypeUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Bug + Grass should be neutral)",
			UType::GetNetModifier({Flying, Ground}, {Bug, Grass},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			1,FTypeUnitTestUtilities::TOLERANCE);
		TestEqual(
			"NetModifier (Flying + Ground [multi-Type] vs. Ground + Fighting should be effective)",
			UType::GetNetModifier({Flying, Ground}, {Ground, Fighting},
				EAttackModifierMode::MultiType, FTypeUnitTestUtilities::DEBUG),
			2,FTypeUnitTestUtilities::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}

	return true;
}