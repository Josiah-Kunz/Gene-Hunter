#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


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

	// Define success:
	const TArray<FTypeArray1D> Expected = {
		
		// Flying singly-Typed defenders 
		FTypeArray1D{{Bug}},
		FTypeArray1D{{Fighting}},
		FTypeArray1D{{Grass}},

		// Ground singly-Typed defenders 
		FTypeArray1D{{Electric}},
		FTypeArray1D{{Fire}},
		FTypeArray1D{{Poison}},
		FTypeArray1D{{Rock}},
		FTypeArray1D{{Steel}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground}, 1,
		UType::Effective, true, EAttackModifierMode::Coverage, Expected, Desc, false);
	TestEqual(
	"Flying/Ground coverage effective attack vs singly-Typed defenders " + Desc,
	bPass, true
	);

	
	
	
	return true;
	
}