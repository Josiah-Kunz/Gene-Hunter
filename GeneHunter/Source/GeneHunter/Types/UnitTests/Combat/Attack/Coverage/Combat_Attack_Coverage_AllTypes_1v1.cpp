#pragma once

#include "GeneHunter/FTypeUnitTestUtilities.h"

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
	const TArray<FTypeArray2*> Expected = {
		new FTypeArray2{{{Bug}}, {}},
		new FTypeArray2{{{Electric}}, {Flying}},
		new FTypeArray2{{{Fighting}}, {}},
		new FTypeArray2{{{Fire}}, {}},
		new FTypeArray2{{{Flying}}, {Bug, Fighting, Grass}},
		new FTypeArray2{{{Grass}}, {Ground}},
		new FTypeArray2{{{Ground}}, {Electric, Fire, Poison, Rock, Steel}},
		new FTypeArray2{{{Ice}}, {Flying, Ground}},
		new FTypeArray2{{{Poison}}, {}},
		new FTypeArray2{{{Rock}}, {Flying}},
		new FTypeArray2{{{Steel}}, {}},
		new FTypeArray2{{{Water}}, {Ground}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = FTypeUnitTestUtilities::DoAnalyzeAll(AllTypes, 1, 1,
		FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
		true, EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"AnalzyeAll 1v1 " + Desc,
	bPass, true
);
	return true;
	
}