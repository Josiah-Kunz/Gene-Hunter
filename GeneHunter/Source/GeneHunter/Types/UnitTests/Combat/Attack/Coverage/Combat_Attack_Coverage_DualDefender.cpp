#pragma once

#include "GeneHunter/Types/UnitTests/Utilities/TypeUnitTestUtilities.h"
#include "GeneHunter/Types/UnitTests/DummyType.h"

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
	const TArray<FTypeArray1D*> Expected = {

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
			new FTypeArray1D{{Bug, Fighting}},
			new FTypeArray1D{{Bug, Fire}},
			new FTypeArray1D{{Bug, Flying}},
			new FTypeArray1D{{Bug, Grass}},
			new FTypeArray1D{{Bug, Ground}},
			new FTypeArray1D{{Bug, Ice}},
			new FTypeArray1D{{Bug, Poison}},
			new FTypeArray1D{{Bug, Water}},

			// (7) Fighting + those listed above - B.ug
			new FTypeArray1D{{Fighting, Fire}},
			new FTypeArray1D{{Fighting, Flying}},
			new FTypeArray1D{{Fighting, Grass}},
			new FTypeArray1D{{Fighting, Ground}},
			new FTypeArray1D{{Fighting, Ice}},
			new FTypeArray1D{{Fighting, Poison}},
			new FTypeArray1D{{Fighting, Water}},

			// (6) Grass + those listed above - B.ug - Fighting
			new FTypeArray1D{{Grass, Fire}},
			new FTypeArray1D{{Grass, Flying}},
			new FTypeArray1D{{Grass, Ground}},
			new FTypeArray1D{{Grass, Ice}},
			new FTypeArray1D{{Grass, Poison}},
			new FTypeArray1D{{Grass, Water}},
			

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
			new FTypeArray1D{{Electric, Fire}},
			new FTypeArray1D{{Electric, Poison}},
			new FTypeArray1D{{Electric, Rock}},
			new FTypeArray1D{{Electric, Steel}},
			new FTypeArray1D{{Electric, Fighting}},
			new FTypeArray1D{{Electric, Ground}},
			new FTypeArray1D{{Electric, Ice}},
			new FTypeArray1D{{Electric, Water}},

			// (6) Fire + those listed above
			new FTypeArray1D{{Fire, Poison}},
			new FTypeArray1D{{Fire, Rock}},
			new FTypeArray1D{{Fire, Steel}},
			//new FTypeArray1D{{Fire, Fighting}}, // already in Flying
			new FTypeArray1D{{Fire, Ground}},
			new FTypeArray1D{{Fire, Ice}},
			new FTypeArray1D{{Fire, Water}},

			// (5) Poison + those listed above
			new FTypeArray1D{{Poison, Rock}},
			new FTypeArray1D{{Poison, Steel}},
			//new FTypeArray1D{{Poison, Fighting}}, // already in Flying
			new FTypeArray1D{{Poison, Ground}},
			new FTypeArray1D{{Poison, Ice}},
			new FTypeArray1D{{Poison, Water}},

			// (5) Rock + those listed above
			new FTypeArray1D{{Rock, Steel}},
			new FTypeArray1D{{Rock, Fighting}},
			new FTypeArray1D{{Rock, Ground}},
			new FTypeArray1D{{Rock, Ice}},
			new FTypeArray1D{{Rock, Water}},

			// (4) Steel + those listed above
			new FTypeArray1D{{Steel, Fighting}},
			new FTypeArray1D{{Steel, Ground}},
			new FTypeArray1D{{Steel, Ice}},
			new FTypeArray1D{{Steel, Water}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllTypes, {Flying, Ground}, 2,
		UType::Effective, true, EAttackModifierMode::Coverage, Expected, Desc, false);
	TestEqual(
	"Flying/Ground coverage effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	return true;
	
}