#pragma once

#include "GeneHunter/Types/UnitTests/FTypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_MultiType_SingleDefender,
	"UType.Combat.Attack.MultiType.Single-Typed Defender",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests a Flying + Ground (because Gliscor) multi-Type attack against every singly-Typed (dummy) defender.
 * The Types that are weak against Flying _and_ Ground simultaneously get reported and tested against.
 */
bool FUType_Combat_Attack_MultiType_SingleDefender::RunTest(const FString& Parameters)
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
			// Singly-Typed defenders
			new FTypeArray1D{{Fire}},
			new FTypeArray1D{{Fighting}},
			new FTypeArray1D{{Poison}},
		};
	
	// Do the tests
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoCombatAnalysis(AllTypes, {Flying, Ground}, 1,
		UType::EFFECTIVE, true, EAttackModifierMode::MultiType, Expected, Desc);
	TestEqual(
	"Flying/Ground multi-Type effective attack vs singly-Typed defenders " + Desc,
	bPass, true
	);

	return true;
	
}