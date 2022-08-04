#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


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

	// Define success 
	const TArray<FTypeArray1D> Expected =
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
		FTypeArray1D{{Fire, Bug}},
		FTypeArray1D{{Fire, Electric}},
		FTypeArray1D{{Fire, Grass}},
		FTypeArray1D{{Fire, Fighting}},
		FTypeArray1D{{Fire, Ground}},
		FTypeArray1D{{Fire, Ice}},
		FTypeArray1D{{Fire, Poison}},
		FTypeArray1D{{Fire, Rock}},
		FTypeArray1D{{Fire, Steel}},
		FTypeArray1D{{Fire, Water}},

		// (9) Fighting + all - Fire
		FTypeArray1D{{Fighting, Bug}},
		FTypeArray1D{{Fighting, Electric}},
		FTypeArray1D{{Fighting, Grass}},
		FTypeArray1D{{Fighting, Ground}},
		FTypeArray1D{{Fighting, Ice}},
		FTypeArray1D{{Fighting, Poison}},
		FTypeArray1D{{Fighting, Rock}},
		FTypeArray1D{{Fighting, Steel}},
		FTypeArray1D{{Fighting, Water}},

		// (8) Poison + all - Fire & Fighting
		FTypeArray1D{{Poison, Bug}},
		FTypeArray1D{{Poison, Electric}},
		FTypeArray1D{{Poison, Grass}},
		FTypeArray1D{{Poison, Ground}},
		FTypeArray1D{{Poison, Ice}},
		FTypeArray1D{{Poison, Rock}},
		FTypeArray1D{{Poison, Steel}},
		FTypeArray1D{{Poison, Water}},
	};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground}, 2,
		UType::Effective, true, EAttackModifierMode::MultiType, Expected, Desc, false);
	TestEqual(
	"Flying/Ground multi-Type effective attack vs dual-Typed defenders " + Desc,
	bPass, true
	);

	
	

	return true;
	
}