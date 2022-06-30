#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

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
	const TArray<FTypeArray1*> Expected =
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
		new FTypeArray1{{Fire, Bug}},
		new FTypeArray1{{Fire, Electric}},
		new FTypeArray1{{Fire, Grass}},
		new FTypeArray1{{Fire, Fighting}},
		new FTypeArray1{{Fire, Ground}},
		new FTypeArray1{{Fire, Ice}},
		new FTypeArray1{{Fire, Poison}},
		new FTypeArray1{{Fire, Rock}},
		new FTypeArray1{{Fire, Steel}},
		new FTypeArray1{{Fire, Water}},

		// (9) Fighting + all - Fire
		new FTypeArray1{{Fighting, Bug}},
		new FTypeArray1{{Fighting, Electric}},
		new FTypeArray1{{Fighting, Grass}},
		new FTypeArray1{{Fighting, Ground}},
		new FTypeArray1{{Fighting, Ice}},
		new FTypeArray1{{Fighting, Poison}},
		new FTypeArray1{{Fighting, Rock}},
		new FTypeArray1{{Fighting, Steel}},
		new FTypeArray1{{Fighting, Water}},

		// (8) Poison + all - Fire & Fighting
		new FTypeArray1{{Poison, Bug}},
		new FTypeArray1{{Poison, Electric}},
		new FTypeArray1{{Poison, Grass}},
		new FTypeArray1{{Poison, Ground}},
		new FTypeArray1{{Poison, Ice}},
		new FTypeArray1{{Poison, Rock}},
		new FTypeArray1{{Poison, Steel}},
		new FTypeArray1{{Poison, Water}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoCombatAnalysis(AllTypes, {Flying, Ground}, 2,
		FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
		true, EAttackModifierMode::MultiType, Expected, Desc);
	TestEqual(
	"Flying/Ground multi-Type effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	return true;
	
}