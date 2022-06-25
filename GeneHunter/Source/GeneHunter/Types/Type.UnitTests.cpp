
#include <string>

#include "Type.h"
#include "DummyType.h"
#include "../FUnitTestUtilities.h"
#include "AITestSuite/Public/AITestsCommon.h"
#include "NavMesh/RecastNavMesh.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_CombineModifiers, "UType.CombineModifiers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests on combining modifiers (e.g., -1 & 2 -> -0.5)
 */
bool FUType_CombineModifiers::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2), -0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1), -1,FUnitTestUtilities::TOLERANCE);

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2), 0,FUnitTestUtilities::TOLERANCE);

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1,FUnitTestUtilities::TOLERANCE);

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1,FUnitTestUtilities::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2,FUnitTestUtilities::TOLERANCE);
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2,FUnitTestUtilities::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4,FUnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_GetDummyTypes, "UType.GetDummyTypes", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Ensures the macro GET_DUMMY_TYPES() works.
 */
bool FUType_GetDummyTypes::RunTest(const FString& Parameters)
{

	// Import types
	GET_DUMMY_TYPES()

	// Number of types
	TestEqual(
				"GET_DUMMY_TYPES number of array elements",
				AllDummyTypes.Num(),
				12,FUnitTestUtilities::TOLERANCE);

	// Non-null types
	TestSame(
		"Bug Type non-null",
		Bug != nullptr,
		true
		);
	
	// Done!
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUType_Analysis, "UType.MatchupAnalysis", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests:
 *		- UType::GetNetModifier
 *		- UType::Analyze
 * This is done as one big test so we don't have to load and assign all the dummy Types several times.
 * TODO: Now that the macro is defined, we can make separate tests!
 */
bool FUType_Analysis::RunTest(const FString& Parameters)
{
#pragma region Get dummy Types

	/*
	TArray<UDummyType*> AllDummyTypes;
	UDummyType::GetAllDummyTypes(AllDummyTypes);
	UDummyType* Bug = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Bug")));
	UDummyType* Electric = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Electric")));
	UDummyType* Fighting = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fighting")));
	UDummyType* Fire = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fire")));
	UDummyType* Flying = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Flying")));
	UDummyType* Grass = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Grass")));
	UDummyType* Ground = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ground")));
	UDummyType* Ice = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ice")));
	UDummyType* Poison = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Poison")));
	UDummyType* Rock = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Rock")));
	UDummyType* Steel = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Steel")));
	UDummyType* Water = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Water")));
	*/

	GET_DUMMY_TYPES()
#pragma endregion
	
#pragma region GetNetModifier tests
	if (Ground)
	{
		FString DeWater = "No";
		if (Water)
			DeWater = Water->GetName();
		TestEqual(
			"GetNetModifier (ineffective single attack vs dual defender) ::" + DeWater + "::",
			UType::GetNetModifier({Ground}, {Fighting, Bug}),
			0.5F,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Bug, Electric}),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Electric}),
			2,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (ineffective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Flying, Electric}, EAttackModifierMode::MultiType),
			0,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Bug, Grass}, EAttackModifierMode::MultiType),
			1,FUnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Ground, Fighting}, EAttackModifierMode::MultiType),
			2,FUnitTestUtilities::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}
#pragma endregion

/*
	
#pragma region Multi-Type Analyze attack test (Flying/Ground analysis because Gliscor)

	// Get array of FTypeArrays (one for each Type in AllDummyTypes)
	TArray<FTypeArrays*> AgainstTypes = {};
	for(UDummyType* DummyType : AllDummyTypes)
	{
		FTypeArrays* DummyTypeArrays = new FTypeArrays{{DummyType}, {}};
		AgainstTypes.Add(DummyTypeArrays);
	}
	
	// Get the UTypes (actual)
	TArray<FTypeArrays*> Analysis = UType::Analyze({Ground, Flying},
		AgainstTypes,
		FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
				EAttackModifierMode::MultiType,
				true
			);

	// Convert FTypeArrays* -> UDummyType*
	TArray<UType*> Actual = {};
	for(FTypeArrays* TypeInfo : Analysis)
		Actual.Add(TypeInfo->TypeArray1[0]);

	// Perform the test
	FString Desc;
	bool bPass = FUnitTestUtilities::TArrayAreEqual(Actual, {Fire, Poison, Fighting}, Desc);
	TestEqual(
		"Flying/Ground multiType attack " + Desc + " " + FString::FromInt(Actual.Num()),
		bPass, true
	);
#pragma endregion

*/
	
	/*
	
#pragma region Coverage Analyze test

	// Get the UTypes (actual)
	Actual = UType::AnalyzeVsSingle(
			{Ground, Flying},
			TArray<UType*>(AllDummyTypes),
			FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
				EAttackModifierMode::Coverage,
				true
			);

	// Perform the test
	bPass = FFUnitTestUtilities::TArrayAreEqual(Actual, {Electric, Fire, Poison, Rock, Steel, Bug, Fighting, Grass}, Desc);
	TestEqual(
		"Flying/Ground coverage attack " + Desc,
		bPass, true
	);
#pragma endregion

#pragma region AnalyzeAll tests

	// AnalyzeAll 1v1 attacking
	Actual = UType::AnalyzeAll(
		TArray<UType*>(AllDummyTypes),
		1, 1, 
		FFloatRange{
					FFloatRangeBound::Inclusive(1),
					FFloatRangeBound::Open()
					},
		true,
		EAttackModifierMode::Coverage
	);

	// Perform the test
	bPass = FFUnitTestUtilities::TArrayAreEqual(
		Actual,
		{Ice, Fire, Steel, Water},
		Desc);
	TestEqual(
		"AnalyzeAll 1v1 atk never resisted" + Desc,
		bPass, true
	);
	
	// AnalyzeAll 2v1 attacking
	Actual = UType::AnalyzeAll(
		TArray<UType*>(AllDummyTypes),
		2, 1, 
		FFloatRange{
					FFloatRangeBound::Exclusive(1),
					FFloatRangeBound::Open()
					},
					true,
					EAttackModifierMode::Coverage
	);

	// Perform the test
	// For the purposes of this test, Water and Ice have been made effective against EVERYTHING
	// (otherwise, the type combinations are too numerous to compute by hand)
	bPass = FFUnitTestUtilities::TArrayAreEqual(
		Actual,
		{
			// Water/Ice + all types
			Ice, Bug, Ice, Electric, Ice, Fighting, Ice, Fire, Ice, Flying, Ice, Grass, Ice, Ground, Ice, Poison, Ice, Rock, Ice, Steel, Ice, Water,
			Water, Bug, Water, Electric, Water, Fighting, Water, Fire, Water, Flying, Water, Grass, Water, Ground, Water, Poison, Water, Rock, Water, Steel,
			// Other "magic" combinations that complement each other
			//Flying, Ground,
			},
		Desc);
	TestEqual(
		"AnalyzeAll 2v1 atk always effective" + Desc,
		bPass, true
	);

	// AnalyzeAll 1v1 defending
    	Actual = UType::AnalyzeAll(
    		TArray<UType*>(AllDummyTypes),
    		1, 1, 
    		FFloatRange{
    					FFloatRangeBound::Open(),
    					FFloatRangeBound::Inclusive(1)
    					},
    					false,
					EAttackModifierMode::Coverage
    	);
    
    	// Perform the test
    	bPass = FFUnitTestUtilities::TArrayAreEqual(
    		Actual,
    		{},
    		Desc);
    	TestEqual(
    		"AnalyzeAll 1v1 def never weak" + Desc,
    		bPass, true
    	);
	
#pragma endregion

*/

#pragma region Sorting tests

	// TODO
	
#pragma endregion
	
	// All passed!
	return true;
}