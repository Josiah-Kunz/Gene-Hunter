#pragma once

#include "GeneHunter/FUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_AnalyzeMultiTypeEffecitveAttack, "UType.AnalyzeMultiTypeAttack", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) multi-Type attack against every singly-Typed and dual-Typed (dummy) defender.
 * The Types that are weak against Flying _and_ Ground simultaneously get reported and tested against.
 */
bool FUType_AnalyzeMultiTypeEffecitveAttack::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success based on index:
	//	- Index [0] for singly-Typed defenders
	//	- Index [1] for doubly-Typed defenders
	TArray<TArray<FTypeArray1*>> Expected = {

		{
			// Singly-Typed defenders
			new FTypeArray1{{Fire}},
			new FTypeArray1{{Fighting}},
			new FTypeArray1{{Poison}},
		},{
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
		}
	};
	
	// Do the tests for 1 or 2 defenders
	for(int NumDefendingType = 0; NumDefendingType < Expected.Num(); NumDefendingType++)
	{
		
		// Get array of FTypeArray1 (one or two for each Type in AllDummyTypes)
		TArray<FTypeArray1*> DefenderTypes = UType::GetAllTypeCombinations(AllTypes, NumDefendingType + 1);
	
		// Get the UTypes (actual) that Ground + Flying are effective against
		TArray<FTypeArray1*> Analysis = UType::Analyze({Ground, Flying},
			DefenderTypes,
			FFloatRange{
					FFloatRangeBound::Exclusive(1),
					FFloatRangeBound::Open()
					},
					EAttackModifierMode::MultiType,
					true,
					true
				);


		// Test it
		FString Desc;
		const bool bPass = FUnitTestUtilities::ArrayOfTypeArray1sAreEqual(Analysis,
			Expected[NumDefendingType], Desc);
		TestEqual(
			"Flying/Ground multiType effective attack " + Desc,
			bPass, true
		);
	}
		
	return true;
	
}