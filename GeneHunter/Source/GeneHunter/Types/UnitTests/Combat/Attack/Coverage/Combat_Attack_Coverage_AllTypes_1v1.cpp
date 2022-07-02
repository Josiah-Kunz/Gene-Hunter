#pragma once

#include "GeneHunter/Types/UnitTests/TypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Attack_Coverage_AllTypes_1v1,
	"UType.Combat.Attack.Coverage.All Types.1v1",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests all dummy Types vs all dummy Types in a single-Type vs single-Type combat.
 * Effective attacks are reported.
 */
bool FUType_Combat_Attack_Coverage_AllTypes_1v1::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success in alphabetical order
	const TArray<FTypeArray2D*> Expected = {
		new FTypeArray2D{{{Bug}}, {}},
		new FTypeArray2D{{{Electric}}, {Flying}},
		new FTypeArray2D{{{Fighting}}, {}},
		new FTypeArray2D{{{Fire}}, {}},
		new FTypeArray2D{{{Flying}}, {Bug, Fighting, Grass}},
		new FTypeArray2D{{{Grass}}, {Ground}},
		new FTypeArray2D{{{Ground}}, {Electric, Fire, Poison, Rock, Steel}},
		new FTypeArray2D{{{Ice}}, {Flying, Ground}},
		new FTypeArray2D{{{Poison}}, {}},
		new FTypeArray2D{{{Rock}}, {Flying}},
		new FTypeArray2D{{{Steel}}, {}},
		new FTypeArray2D{{{Water}}, {Ground}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestAnalyzeAll(AllTypes, 1, 1,
		UType::EFFECTIVE, true, EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"AnalzyeAll 1v1 (offensive) " + Desc,
	bPass, true
);
	return true;
	
}