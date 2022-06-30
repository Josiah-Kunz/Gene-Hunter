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
	const TArray<FTypeArray1D*> Expected = {
		
		// Flying singly-Typed defenders 
		new FTypeArray1D{{Bug}},
		new FTypeArray1D{{Fighting}},
		new FTypeArray1D{{Grass}},

		// Ground singly-Typed defenders 
		new FTypeArray1D{{Electric}},
		new FTypeArray1D{{Fire}},
		new FTypeArray1D{{Poison}},
		new FTypeArray1D{{Rock}},
		new FTypeArray1D{{Steel}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoCombatAnalysis(AllTypes, {Flying, Ground}, 1,
		UType::EFFECTIVE, true, EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"Flying/Ground coverage effective attack vs singly-Typed defenders " + Desc,
	bPass, true
);
	return true;
	
}