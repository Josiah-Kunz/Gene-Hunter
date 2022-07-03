#pragma once

#include "GeneHunter/Types/UnitTests/Utilities/TypeUnitTestUtilities.h"
#include "GeneHunter/Types/UnitTests/DummyType.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Combat_Defend_Coverage_AllTypes_1v1,
	"UType.Combat.Defend.Coverage.All Types.1v1",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests all dummy Types vs all dummy Types in a single-Type vs single-Type combat.
 * Effective attacks are reported.
 */
bool FUType_Combat_Defend_Coverage_AllTypes_1v1::RunTest(const FString& Parameters)
{

	// Get all types
	GET_DUMMY_TYPES()

	// Convert to UType* (for functions' sakes)
	TArray<UType*> AllTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
		AllTypes.Add(DummyType);

	// Define success in alphabetical order
	const TArray<FTypeArray2D*> Expected = {
		new FTypeArray2D{{{Bug}}, {Ground}},
		new FTypeArray2D{{{Electric}}, {Flying}},
		new FTypeArray2D{{{Fighting}}, {Bug}},
		new FTypeArray2D{{{Fire}}, {Bug}},
		new FTypeArray2D{{{Flying}}, {Ground, Bug, Fighting, Grass}},
		new FTypeArray2D{{{Grass}}, {Ground}},
		new FTypeArray2D{{{Ground}}, {Electric, Poison, Rock}},
		new FTypeArray2D{{{Ice}}, {}},
		new FTypeArray2D{{{Poison}}, {}},
		new FTypeArray2D{{{Rock}}, {Flying}},
		new FTypeArray2D{{{Steel}}, {Flying}},
		new FTypeArray2D{{{Water}}, {}},
		};
		
	// Do the test
	FString Desc = "";
	const bool bPass = UTypeUnitTestUtilities::TestAnalyzeAll(AllTypes, 1, 1,
		UType::Ineffective,
		false, EAttackModifierMode::Coverage, Expected, Desc);
	TestEqual(
	"AnalzyeAll 1v1 (defensive) " + Desc,
	bPass, true
);
	return true;
	
}