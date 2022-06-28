#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_Coverage_DualDefender,
	"UType.Combat.Attack.Coverage.Dual-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "coverage" attack against every dual-Typed (dummy) defender.
 * The Types that are weak against Flying _or_ Ground separately get reported and tested against.
 */
bool FUType_Combat_Attack_Coverage_DualDefender::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success:
	const TArray<FTypeArray1*> Expected = {

			/* Doubly-Typed defenders
			 *
			 * Flying advantages are (3):
			 *	- B.ug
			 *	- Fighting
			 *	- Grass
			 *
			 * Flying neutrals are (6):
			 *	- Fire
			 *  - Flying
			 *  - Ground
			 *  - Ice
			 *  - Poison
			 *  - Water
			 */
			
			// (8) B.ug + those listed above
			new FTypeArray1{{Bug, Fighting}},
			new FTypeArray1{{Bug, Fire}},
			new FTypeArray1{{Bug, Flying}},
			new FTypeArray1{{Bug, Grass}},
			new FTypeArray1{{Bug, Ground}},
			new FTypeArray1{{Bug, Ice}},
			new FTypeArray1{{Bug, Poison}},
			new FTypeArray1{{Bug, Water}},

			// (7) Fighting + those listed above - B.ug
			new FTypeArray1{{Fighting, Fire}},
			new FTypeArray1{{Fighting, Flying}},
			new FTypeArray1{{Fighting, Grass}},
			new FTypeArray1{{Fighting, Ground}},
			new FTypeArray1{{Fighting, Ice}},
			new FTypeArray1{{Fighting, Poison}},
			new FTypeArray1{{Fighting, Water}},

			// (6) Grass + those listed above - B.ug - Fighting
			new FTypeArray1{{Grass, Fire}},
			new FTypeArray1{{Grass, Flying}},
			new FTypeArray1{{Grass, Ground}},
			new FTypeArray1{{Grass, Ice}},
			new FTypeArray1{{Grass, Poison}},
			new FTypeArray1{{Grass, Water}},
			

			/* Ground advantages are (5):
			 *	- Electric
			 *	- Fire
			 *	- Poison
			 *	- Rock
			 *	- Steel
			 *
			 * Ground neutrals are (4):
			 *	- Fighting --- careful! Fighting + Fire//Poison already accounted for in Flying
			 *	- Ground
			 *	- Ice
			 *	- Water
			 */

			// (8) Electric + those listed above
			new FTypeArray1{{Electric, Fire}},
			new FTypeArray1{{Electric, Poison}},
			new FTypeArray1{{Electric, Rock}},
			new FTypeArray1{{Electric, Steel}},
			new FTypeArray1{{Electric, Fighting}},
			new FTypeArray1{{Electric, Ground}},
			new FTypeArray1{{Electric, Ice}},
			new FTypeArray1{{Electric, Water}},

			// (6) Fire + those listed above
			new FTypeArray1{{Fire, Poison}},
			new FTypeArray1{{Fire, Rock}},
			new FTypeArray1{{Fire, Steel}},
			//new FTypeArray1{{Fire, Fighting}}, // already in Flying
			new FTypeArray1{{Fire, Ground}},
			new FTypeArray1{{Fire, Ice}},
			new FTypeArray1{{Fire, Water}},

			// (5) Poison + those listed above
			new FTypeArray1{{Poison, Rock}},
			new FTypeArray1{{Poison, Steel}},
			//new FTypeArray1{{Poison, Fighting}}, // already in Flying
			new FTypeArray1{{Poison, Ground}},
			new FTypeArray1{{Poison, Ice}},
			new FTypeArray1{{Poison, Water}},

			// (5) Rock + those listed above
			new FTypeArray1{{Rock, Steel}},
			new FTypeArray1{{Rock, Fighting}},
			new FTypeArray1{{Rock, Ground}},
			new FTypeArray1{{Rock, Ice}},
			new FTypeArray1{{Rock, Water}},

			// (4) Steel + those listed above
			new FTypeArray1{{Steel, Fighting}},
			new FTypeArray1{{Steel, Ground}},
			new FTypeArray1{{Steel, Ice}},
			new FTypeArray1{{Steel, Water}},
	};
	
	// Do the testsFString Desc = "";
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoAttackAnalysis(AllTypes, {Flying, Ground}, 2,
		EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"Flying/Ground coverage effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	return true;
	
}