#pragma once


#include "Utilities/TypeUnitTestUtilities.h"

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

	// Define success:
	const TArray<FTypeArray1D*> Expected = {

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
		new FTypeArray1D{{Ground, Bug}},
		new FTypeArray1D{{Ground, Fighting}},
		new FTypeArray1D{{Ground, Electric}},
		new FTypeArray1D{{Ground, Poison}},

		// B.ug + others - Ground
		new FTypeArray1D{{Bug, Fighting}},
		new FTypeArray1D{{Bug, Electric}},
		new FTypeArray1D{{Bug, Poison}},

		// Fighting + others - Ground - B.ug
		new FTypeArray1D{{Fighting, Electric}},
		new FTypeArray1D{{Fighting, Poison}},

		// Electric + others - Ground/B.ug/Fighting
		new FTypeArray1D{{Electric, Poison}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground},
		2, UType::Ineffective, false, EAttackModifierMode::Coverage, Expected, Desc, false);
	TestEqual(
	"Flying/Ground resisted vs (coverage) dual-Typed attackers " + Desc,
	bPass, true
	);
	
	
	

	return true;
	
}