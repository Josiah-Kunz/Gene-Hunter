#pragma once

#include "TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Defend_Coverage_SingleAttacker,
	"__GeneHunter.UType.Combat.Defend.Coverage.Single-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "coverage" defense against every single-Typed (dummy) attacker.
 * The single Types that Flying + Ground resist get reported and tested against.
 */
bool FUType_Combat_Defend_Coverage_SingleAttacker::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Define success:
	const TArray<FTypeArray1D> Expected = {

		/* Flying singly resists:
		 *	- Ground
		 *	- B.ug
		 *	- Fighting
		 *	- Grass [no; Ground is weak to Grass]
		 */ 
		FTypeArray1D{{Ground}},
		FTypeArray1D{{Bug}},
		FTypeArray1D{{Fighting}},

		/*
		 * Ground singly resists:
		 *  - Electric [immunity trumps Flying's weakness]
		 *  - Poison
		 *  - Rock [no; Flying is weak to Rock]
		 */
		FTypeArray1D{{Electric}},
		FTypeArray1D{{Poison}},
		
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground},
		1, UType::Ineffective, false, EAttackModifierMode::Coverage, Expected, Desc, false);
	TestEqual(
	"Flying/Ground resisted vs (multiType) single-Typed attackers " + Desc,
	bPass, true
	);

	
	

	return true;
	
}