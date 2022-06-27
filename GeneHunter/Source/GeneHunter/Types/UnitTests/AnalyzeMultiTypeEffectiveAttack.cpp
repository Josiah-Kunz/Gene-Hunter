#pragma once

#include "GeneHunter/FUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_AnalyzeMultiTypeEffecitveAttack, "UType.AnalyzeMultiTypeAttack", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) multi-Type attack against every singly-Typed and dual-Typed (dummy) defender.
 * The Types that are weak against Flying + Ground get reported and tested against.
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
			// Doubly-Typed defenders

			// Fire + whatever
			new FTypeArray1{{Fire, Fighting}},
			new FTypeArray1{{Fire, Ground}},
			new FTypeArray1{{Fire, Ice}},
			new FTypeArray1{{Fire, Poison}},
			new FTypeArray1{{Fire, Water}},

			// Fighting + whatever
			new FTypeArray1{{Fighting, Ground}},
			new FTypeArray1{{Fighting, Ice}},
			new FTypeArray1{{Fighting, Poison}},
			new FTypeArray1{{Fighting, Water}},

			// Poison + whatever
			new FTypeArray1{{Poison, Ground}},
			new FTypeArray1{{Poison, Ice}},
			new FTypeArray1{{Poison, Water}},
		}
	};
	
	// Do the tests for 1 or 2 defenders
	for(int NumDefendingType = 1; NumDefendingType < Expected.Num(); NumDefendingType++)
	{
		// Get array of FTypeArray1 (one or two for each Type in AllDummyTypes)
		TArray<FTypeArray1*> DefenderTypes = UType::GetAllTypeCombinations(AllTypes, NumDefendingType);
	
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

		// TODO: Don't do this and instead write a new function FTypeArraysAreEqual (like TArrayAreEqual)
		// Convert FTypeArray1* -> UDummyType*
		TArray<UType*> Actual = {};
		for(FTypeArray1* TypeInfo : Analysis)
			if (TypeInfo && TypeInfo->TypeArray.Num() > 0)
				Actual.Add(TypeInfo->TypeArray[0]);

		// Perform the test
		FString Desc;
		bool bPass = FUnitTestUtilities::TypesAndDummiesAreEqual(Actual, {Fire, Poison, Fighting}, Desc);
		TestEqual(
			"Flying/Ground multiType effective attack " + Desc,
			bPass, true
		);
	}
		
	return true;
	
}