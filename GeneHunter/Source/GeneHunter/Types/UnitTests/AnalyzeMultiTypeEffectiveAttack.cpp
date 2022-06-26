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

	// Define success
	TArray<TArray<FTypeArrays*>> Expected = {

		{
			// Singly-Typed defenders
			new FTypeArrays{{Fire}, {}},
			new FTypeArrays{{Fighting}, {}},
			new FTypeArrays{{Poison}, {}},
		},{
			// Doubly-Typed defenders

			// Fire + whatever
			new FTypeArrays{{Fire, Fighting}},
			new FTypeArrays{{Fire, Ground}},
			new FTypeArrays{{Fire, Ice}},
			new FTypeArrays{{Fire, Poison}},
			new FTypeArrays{{Fire, Water}},

			// Fighting + whatever
			new FTypeArrays{{Fighting, Ground}},
			new FTypeArrays{{Fighting, Ice}},
			new FTypeArrays{{Fighting, Poison}},
			new FTypeArrays{{Fighting, Water}},

			// Poison + whatever
			new FTypeArrays{{Poison, Ground}},
			new FTypeArrays{{Poison, Ice}},
			new FTypeArrays{{Poison, Water}},
		}
	}; 
	
	// Do the tests for 1 or 2 defenders
	for(int NumDefendingType = 1; NumDefendingType < Expected.Num(); NumDefendingType++)
	{
		// Get array of FTypeArrays (one or two for each Type in AllDummyTypes)
		TArray<FTypeArrays*> DefenderTypes = UType::GetAllTypeCombinations(AllTypes, NumDefendingType);
	
		// Get the UTypes (actual) that Ground + Flying are effective against
		TArray<FTypeArrays*> Analysis = UType::Analyze({Ground, Flying},
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
		// Convert FTypeArrays* -> UDummyType*
		TArray<UType*> Actual = {};
		for(FTypeArrays* TypeInfo : Analysis)
			if (TypeInfo && TypeInfo->TypeArray1.Num() > 0)
				Actual.Add(TypeInfo->TypeArray1[0]);

		// Perform the test
		FString Desc;
		bool bPass = FUnitTestUtilities::TArrayAreEqual(Actual, {Fire, Poison, Fighting}, Desc);
		TestEqual(
			"Flying/Ground multiType effective attack " + Desc,
			bPass, true
		);
	}
		
	return true;
	
}