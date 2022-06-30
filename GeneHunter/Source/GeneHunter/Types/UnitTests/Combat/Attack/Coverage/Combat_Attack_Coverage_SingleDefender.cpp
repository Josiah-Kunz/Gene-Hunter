#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_Coverage_SingleDefender,
	"UType.Combat.Attack.Coverage.Single-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) "coverage" attack against every singly-Typed (dummy) defender.
 * The Types that are weak against Flying _or_ Ground separately get reported and tested against.
 */
bool FUType_Combat_Attack_Coverage_SingleDefender::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success:
	const TArray<FTypeArray1*> Expected = {
		
		// Flying singly-Typed defenders 
		new FTypeArray1{{Bug}},
		new FTypeArray1{{Fighting}},
		new FTypeArray1{{Grass}},

		// Ground singly-Typed defenders 
		new FTypeArray1{{Electric}},
		new FTypeArray1{{Fire}},
		new FTypeArray1{{Poison}},
		new FTypeArray1{{Rock}},
		new FTypeArray1{{Steel}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoCombatAnalysis(AllTypes, {Flying, Ground}, 1,
		FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
		true, EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"Flying/Ground coverage effective attack vs singly-Typed defenders " + Desc,
	bPass, true
);
	return true;
	
}