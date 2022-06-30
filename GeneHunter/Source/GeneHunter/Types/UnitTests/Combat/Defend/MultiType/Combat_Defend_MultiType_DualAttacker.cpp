#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

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
		new FTypeArray1{{Ground, Bug}},
		new FTypeArray1{{Ground, Fighting}},
		new FTypeArray1{{Ground, Grass}},
		new FTypeArray1{{Ground, Electric}},
		new FTypeArray1{{Ground, Poison}},
		new FTypeArray1{{Ground, Rock}},

		// B.ug + others
		new FTypeArray1{{Bug, Fighting}},
		new FTypeArray1{{Bug, Grass}}, // Ex: Flying vs [B.ug, Grass] -> 1/4x || Ground vs. [B.ug, Grass] -> 2x ==> Total is 1/2x
		new FTypeArray1{{Bug, Electric}},
		new FTypeArray1{{Bug, Poison}},
		new FTypeArray1{{Bug, Rock}}, // Flying vs [B.ug, Rock] -> 1x

		// Fighting + others
		new FTypeArray1{{Fighting, Grass}},
		new FTypeArray1{{Fighting, Electric}},
		new FTypeArray1{{Fighting, Poison}},
		new FTypeArray1{{Fighting, Rock}},

		// Grass + others
		new FTypeArray1{{Grass, Electric}},
		new FTypeArray1{{Grass, Poison}},
		//new FTypeArray1{{Grass, Rock}}, // Flying vs [Grass, Rock] -> 1x || Ground -> 1x

		// Electric + others
		new FTypeArray1{{Electric, Poison}},
		new FTypeArray1{{Electric, Rock}},

		// Poison
		new FTypeArray1{{Poison, Rock}}, // Flying -> 2x || Ground -> 1/4x

		/* Neutrals + others -Grass -Rock
		 *	- Fire
		 *	- Flying
		 *	- Steel
		 */

		// Fire
		new FTypeArray1{{Fire, Ground}},
		new FTypeArray1{{Fire, Bug}},
		new FTypeArray1{{Fire, Fighting}},
		//new FTypeArray1{{Fire, Grass}}, // Flying -> 1/2x || Ground -> 2x
		new FTypeArray1{{Fire, Electric}},
		new FTypeArray1{{Fire, Poison}},

		// Flying
		new FTypeArray1{{Flying, Ground}},
		new FTypeArray1{{Flying, Bug}},
		new FTypeArray1{{Flying, Fighting}},
		new FTypeArray1{{Flying, Electric}},
		new FTypeArray1{{Flying, Poison}},

		// Steel
		new FTypeArray1{{Steel, Ground}},
		new FTypeArray1{{Steel, Bug}},
		new FTypeArray1{{Steel, Fighting}},
		new FTypeArray1{{Steel, Electric}},
		new FTypeArray1{{Steel, Poison}},

		// Immunes get everything (even Ice!)
		new FTypeArray1{{Electric, Ice}},
		new FTypeArray1{{Electric, Water}},
		new FTypeArray1{{Ground, Ice}},
		new FTypeArray1{{Ground, Water}},

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
		EAttackModifierMode::MultiType, Expected, Desc);
	TestEqual(
	"Flying/Ground resisted vs (multiType) dual-Typed attackers " + Desc,
	bPass, true
	);

	return true;
	
}