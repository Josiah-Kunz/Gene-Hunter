#pragma once

#include "Utilities/TypeUnitTestUtilities.h"
#include "DummyType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_MultiType_DualDefender,
	"UType.Combat.Attack.MultiType.Dual-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) multi-Type attack against every dual-Typed (dummy) defender.
 * The Types that are weak against Flying _and_ Ground simultaneously get reported and tested against.
 */
bool FUType_Combat_Attack_MultiType_DualDefender::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success 
	const TArray<FTypeArray1D*> Expected =
	{
		/* Doubly-Typed defenders
		 *
		 * This formula is (generally):
		 *		SUM_[i=1] ^[N] (i + k - 1)
		 *	where	N = number of effectives
		 *			k = number of neutrals
		 *
		 * Base advantages are (3):
		 *	- Fire
		 *	- Fighting
		 *	- Poison
		 *
		 * Base neutrals are (8):
   		 *	- B.ug
   		 *	- Electric
		 *	- Grass
		 *	- Ground
		 *	- Ice
		 *	- Rock
		 *	- Steel
		 *	- Water
		 */
		
		// (10) Fire + those listed above
		new FTypeArray1D{{Fire, Bug}},
		new FTypeArray1D{{Fire, Electric}},
		new FTypeArray1D{{Fire, Grass}},
		new FTypeArray1D{{Fire, Fighting}},
		new FTypeArray1D{{Fire, Ground}},
		new FTypeArray1D{{Fire, Ice}},
		new FTypeArray1D{{Fire, Poison}},
		new FTypeArray1D{{Fire, Rock}},
		new FTypeArray1D{{Fire, Steel}},
		new FTypeArray1D{{Fire, Water}},

		// (9) Fighting + all - Fire
		new FTypeArray1D{{Fighting, Bug}},
		new FTypeArray1D{{Fighting, Electric}},
		new FTypeArray1D{{Fighting, Grass}},
		new FTypeArray1D{{Fighting, Ground}},
		new FTypeArray1D{{Fighting, Ice}},
		new FTypeArray1D{{Fighting, Poison}},
		new FTypeArray1D{{Fighting, Rock}},
		new FTypeArray1D{{Fighting, Steel}},
		new FTypeArray1D{{Fighting, Water}},

		// (8) Poison + all - Fire & Fighting
		new FTypeArray1D{{Poison, Bug}},
		new FTypeArray1D{{Poison, Electric}},
		new FTypeArray1D{{Poison, Grass}},
		new FTypeArray1D{{Poison, Ground}},
		new FTypeArray1D{{Poison, Ice}},
		new FTypeArray1D{{Poison, Rock}},
		new FTypeArray1D{{Poison, Steel}},
		new FTypeArray1D{{Poison, Water}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllTypes, {Flying, Ground}, 2,
		UType::Effective, true, EAttackModifierMode::MultiType, Expected, Desc, false);
	TestEqual(
	"Flying/Ground multi-Type effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	return true;
	
}