#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Defend_Coverage_DualAttacker,
	"UType.Combat.Defend.Coverage.Dual-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "coverage" defense against every dual-Typed (dummy) attacker.
 * The dual Types that Flying + Ground resist get reported and tested against.
 */
bool FUType_Combat_Defend_Coverage_DualAttacker::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success:
	const TArray<FTypeArray1*> Expected = {

		/* Flying singly resists:
		 *	- Ground
		 *	- B.ug
		 *	- Fighting
		 *	- Grass [no; Ground is weak to Grass]
		 *
		 * Ground singly resists:
		 *  - Electric [immunity trumps Flying's weakness]
		 *  - Poison
		 *  - Rock [no; Flying is weak to Rock]
		 *
		 * The intersection of the two are "expected"
		 */

		// Ground + others
		new FTypeArray1{{Ground, Bug}},
		new FTypeArray1{{Ground, Fighting}},
		new FTypeArray1{{Ground, Electric}},
		new FTypeArray1{{Ground, Poison}},

		// B.ug + others - Ground
		new FTypeArray1{{Bug, Fighting}},
		new FTypeArray1{{Bug, Electric}},
		new FTypeArray1{{Bug, Poison}},

		// Fighting + others - Ground - B.ug
		new FTypeArray1{{Fighting, Electric}},
		new FTypeArray1{{Fighting, Poison}},

		// Electric + others - Ground/B.ug/Fighting
		new FTypeArray1{{Electric, Poison}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoCombatAnalysis(AllTypes, {Flying, Ground},
		2,
		FFloatRange{
			FFloatRangeBound::Open(),
			FFloatRangeBound::Exclusive(1)
		},
		false,
		EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"Flying/Ground resisted vs (coverage) dual-Typed attackers " + Desc,
	bPass, true
	);

	return true;
	
}