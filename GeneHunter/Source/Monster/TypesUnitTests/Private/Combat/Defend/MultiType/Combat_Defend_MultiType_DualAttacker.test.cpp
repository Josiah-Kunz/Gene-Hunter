#pragma once

#include "Utilities/TypeUnitTestUtilities.h"
#include "DummyType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Defend_MultiType_DualAttacker,
	"UType.Combat.Defend.MultiType.Dual-Typed Defender",
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
	const TArray<FTypeArray1D*> Expected = {

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
		new FTypeArray1D{{Ground, Bug}},
		new FTypeArray1D{{Ground, Fighting}},
		new FTypeArray1D{{Ground, Grass}},
		new FTypeArray1D{{Ground, Electric}},
		new FTypeArray1D{{Ground, Poison}},
		new FTypeArray1D{{Ground, Rock}},

		// B.ug + others
		new FTypeArray1D{{Bug, Fighting}},
		new FTypeArray1D{{Bug, Grass}}, // Ex: Flying vs [B.ug, Grass] -> 1/4x || Ground vs. [B.ug, Grass] -> 2x ==> Total is 1/2x
		new FTypeArray1D{{Bug, Electric}},
		new FTypeArray1D{{Bug, Poison}},
		new FTypeArray1D{{Bug, Rock}}, // Flying vs [B.ug, Rock] -> 1x

		// Fighting + others
		new FTypeArray1D{{Fighting, Grass}},
		new FTypeArray1D{{Fighting, Electric}},
		new FTypeArray1D{{Fighting, Poison}},
		new FTypeArray1D{{Fighting, Rock}},

		// Grass + others
		new FTypeArray1D{{Grass, Electric}},
		new FTypeArray1D{{Grass, Poison}},
		//new FTypeArray1D{{Grass, Rock}}, // Flying vs [Grass, Rock] -> 1x || Ground -> 1x

		// Electric + others
		new FTypeArray1D{{Electric, Poison}},
		new FTypeArray1D{{Electric, Rock}},

		// Poison
		new FTypeArray1D{{Poison, Rock}}, // Flying -> 2x || Ground -> 1/4x

		/* Neutrals + others -Grass -Rock
		 *	- Fire
		 *	- Flying
		 *	- Steel
		 */

		// Fire
		new FTypeArray1D{{Fire, Ground}},
		new FTypeArray1D{{Fire, Bug}},
		new FTypeArray1D{{Fire, Fighting}},
		//new FTypeArray1D{{Fire, Grass}}, // Flying -> 1/2x || Ground -> 2x
		new FTypeArray1D{{Fire, Electric}},
		new FTypeArray1D{{Fire, Poison}},

		// Flying
		new FTypeArray1D{{Flying, Ground}},
		new FTypeArray1D{{Flying, Bug}},
		new FTypeArray1D{{Flying, Fighting}},
		new FTypeArray1D{{Flying, Electric}},
		new FTypeArray1D{{Flying, Poison}},

		// Steel
		new FTypeArray1D{{Steel, Ground}},
		new FTypeArray1D{{Steel, Bug}},
		new FTypeArray1D{{Steel, Fighting}},
		new FTypeArray1D{{Steel, Electric}},
		new FTypeArray1D{{Steel, Poison}},

		// Immunes get everything (even Ice!)
		new FTypeArray1D{{Electric, Ice}},
		new FTypeArray1D{{Electric, Water}},
		new FTypeArray1D{{Ground, Ice}},
		new FTypeArray1D{{Ground, Water}},

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