#pragma once

#include "TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_Coverage_DualDefender,
	"__GeneHunter.UType.Combat.Attack.Coverage.Dual-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "coverage" attack against every dual-Typed (dummy) defender.
 * The Types that are weak against Flying _or_ Ground separately get reported and tested against.
 */
bool FUType_Combat_Attack_Coverage_DualDefender::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Define success:
	TArray<FTypeArray1D> Expected = {

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
			FTypeArray1D{{Bug, Fighting}},
			FTypeArray1D{{Bug, Fire}},
			FTypeArray1D{{Bug, Flying}},
			FTypeArray1D{{Bug, Grass}},
			FTypeArray1D{{Bug, Ground}},
			FTypeArray1D{{Bug, Ice}},
			FTypeArray1D{{Bug, Poison}},
			FTypeArray1D{{Bug, Water}},

			// (7) Fighting + those listed above - B.ug
			FTypeArray1D{{Fighting, Fire}},
			FTypeArray1D{{Fighting, Flying}},
			FTypeArray1D{{Fighting, Grass}},
			FTypeArray1D{{Fighting, Ground}},
			FTypeArray1D{{Fighting, Ice}},
			FTypeArray1D{{Fighting, Poison}},
			FTypeArray1D{{Fighting, Water}},

			// (6) Grass + those listed above - B.ug - Fighting
			FTypeArray1D{{Grass, Fire}},
			FTypeArray1D{{Grass, Flying}},
			FTypeArray1D{{Grass, Ground}},
			FTypeArray1D{{Grass, Ice}},
			FTypeArray1D{{Grass, Poison}},
			FTypeArray1D{{Grass, Water}},
			

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
			FTypeArray1D{{Electric, Fire}},
			FTypeArray1D{{Electric, Poison}},
			FTypeArray1D{{Electric, Rock}},
			FTypeArray1D{{Electric, Steel}},
			FTypeArray1D{{Electric, Fighting}},
			FTypeArray1D{{Electric, Ground}},
			FTypeArray1D{{Electric, Ice}},
			FTypeArray1D{{Electric, Water}},

			// (6) Fire + those listed above
			FTypeArray1D{{Fire, Poison}},
			FTypeArray1D{{Fire, Rock}},
			FTypeArray1D{{Fire, Steel}},
			//FTypeArray1D{{Fire, Fighting}}, // already in Flying
			FTypeArray1D{{Fire, Ground}},
			FTypeArray1D{{Fire, Ice}},
			FTypeArray1D{{Fire, Water}},

			// (5) Poison + those listed above
			FTypeArray1D{{Poison, Rock}},
			FTypeArray1D{{Poison, Steel}},
			//FTypeArray1D{{Poison, Fighting}}, // already in Flying
			FTypeArray1D{{Poison, Ground}},
			FTypeArray1D{{Poison, Ice}},
			FTypeArray1D{{Poison, Water}},

			// (5) Rock + those listed above
			FTypeArray1D{{Rock, Steel}},
			FTypeArray1D{{Rock, Fighting}},
			FTypeArray1D{{Rock, Ground}},
			FTypeArray1D{{Rock, Ice}},
			FTypeArray1D{{Rock, Water}},

			// (4) Steel + those listed above
			FTypeArray1D{{Steel, Fighting}},
			FTypeArray1D{{Steel, Ground}},
			FTypeArray1D{{Steel, Ice}},
			FTypeArray1D{{Steel, Water}},
	};

	

	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground}, 2,
		UType::Effective, true, EAttackModifierMode::Coverage, Expected, Desc, false);
	TestEqual(
	"Flying/Ground coverage effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	
	
	
	return bPass;
	
}