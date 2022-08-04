#pragma once

#include "Utilities/TypeUnitTestUtilities.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_MultiType_SingleDefender,
	"GeneHunter.UType.Combat.Attack.MultiType.Single-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) multi-Type attack against every singly-Typed (dummy) defender.
 * The Types that are weak against Flying _and_ Ground simultaneously get reported and tested against.
 */
bool FUType_Combat_Attack_MultiType_SingleDefender::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Define success 
	const TArray<FTypeArray1D> Expected =
		{
			// Singly-Typed defenders
			FTypeArray1D{{Fire}},
			FTypeArray1D{{Fighting}},
			FTypeArray1D{{Poison}},
		};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestCombatAnalysis(AllDummyTypes, {Flying, Ground}, 1,
		UType::Effective, true, EAttackModifierMode::MultiType, Expected, Desc, false);
	TestEqual(
	"Flying/Ground multi-Type effective attack vs singly-Typed defenders " + Desc,
	bPass, true
	);

	
	

	return true;
	
}