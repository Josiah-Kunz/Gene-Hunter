#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Defend_MultiType_DualAttacker,
	"GeneHunter.UType.Combat.Defend.MultiType.Dual-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "multiType" defense against every dual-Typed (dummy) attacker.
 * The dual Types that Flying + Ground resist get reported and tested against.
 */
bool FUType_Combat_Defend_MultiType_DualAttacker::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Define success:
	const TArray<FTypeArray1D> Expected = {

		/* Flying singly resists:
		 *	- Ground
		 *	- B.ug
		 *	- Fighting
		 *	- Grass
		 *
		 * Ground singly resists:
		 *  - Electric [immunity trumps Flying's weakness]
		 *  - Poison
		 *  - Rock
		 *
		 * The intersection of the two are "expected"
		 */

		// Ground + all others (because immunity trumps effective attacks)
		FTypeArray1D{{Ground, Bug}},
		FTypeArray1D{{Ground, Fighting}},
		FTypeArray1D{{Ground, Grass}},
		FTypeArray1D{{Ground, Electric}},
		FTypeArray1D{{Ground, Poison}},
		FTypeArray1D{{Ground, Rock}},

		// B.ug + others
		FTypeArray1D{{Bug, Fighting}},
		FTypeArray1D{{Bug, Grass}}, // Ex: Flying vs [B.ug, Grass] -> 1/4x || Ground vs. [B.ug, Grass] -> 2x ==> Total is 1/2x
		FTypeArray1D{{Bug, Electric}},
		FTypeArray1D{{Bug, Poison}},
		FTypeArray1D{{Bug, Rock}}, // Flying vs [B.ug, Rock] -> 1x

		// Fighting + others
		FTypeArray1D{{Fighting, Grass}},
		FTypeArray1D{{Fighting, Electric}},
		FTypeArray1D{{Fighting, Poison}},
		FTypeArray1D{{Fighting, Rock}},

		// Grass + others
		FTypeArray1D{{Grass, Electric}},
		FTypeArray1D{{Grass, Poison}},
		//FTypeArray1D{{Grass, Rock}}, // Flying vs [Grass, Rock] -> 1x || Ground -> 1x

		// Electric + others
		FTypeArray1D{{Electric, Poison}},
		FTypeArray1D{{Electric, Rock}},

		// Poison
		FTypeArray1D{{Poison, Rock}}, // Flying -> 2x || Ground -> 1/4x

		/* Neutrals + others -Grass -Rock
		 *	- Fire
		 *	- Flying
		 *	- Steel
		 */

		// Fire
		FTypeArray1D{{Fire, Ground}},
		FTypeArray1D{{Fire, Bug}},
		FTypeArray1D{{Fire, Fighting}},
		//FTypeArray1D{{Fire, Grass}}, // Flying -> 1/2x || Ground -> 2x
		FTypeArray1D{{Fire, Electric}},
		FTypeArray1D{{Fire, Poison}},

		// Flying
		FTypeArray1D{{Flying, Ground}},
		FTypeArray1D{{Flying, Bug}},
		FTypeArray1D{{Flying, Fighting}},
		FTypeArray1D{{Flying, Electric}},
		FTypeArray1D{{Flying, Poison}},

		// Steel
		FTypeArray1D{{Steel, Ground}},
		FTypeArray1D{{Steel, Bug}},
		FTypeArray1D{{Steel, Fighting}},
		FTypeArray1D{{Steel, Electric}},
		FTypeArray1D{{Steel, Poison}},

		// Immunes get everything (even Ice!)
		FTypeArray1D{{Electric, Ice}},
		FTypeArray1D{{Electric, Water}},
		FTypeArray1D{{Ground, Ice}},
		FTypeArray1D{{Ground, Water}},

	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground},
		2,
		FFloatRange{
			FFloatRangeBound::Open(),
			FFloatRangeBound::Exclusive(1)
		},
		false, EAttackModifierMode::MultiType, Expected, Desc, false);
	TestEqual(
	"Flying/Ground resisted vs (multiType) dual-Typed attackers " + Desc,
	bPass, true
	);

	
	

	return true;
	
}