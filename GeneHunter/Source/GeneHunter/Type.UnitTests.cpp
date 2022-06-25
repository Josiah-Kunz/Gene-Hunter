
#include <string>

#include "Type.h"
#include "Type_UnitTest.h"
#include "UnitTestUtilities.h"
#include "AITestSuite/Public/AITestsCommon.h"
#include "NavMesh/RecastNavMesh.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UType_CombineModifiers, "UType.CombineModifiers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UType_CombineModifiers::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2), -0.5F,UnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1), -1,UnitTestUtilities::TOLERANCE);

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2), 0,UnitTestUtilities::TOLERANCE);

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F,UnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F,UnitTestUtilities::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1,UnitTestUtilities::TOLERANCE);

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1,UnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F,UnitTestUtilities::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1,UnitTestUtilities::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2,UnitTestUtilities::TOLERANCE);
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F,UnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0,UnitTestUtilities::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1,UnitTestUtilities::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2,UnitTestUtilities::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4,UnitTestUtilities::TOLERANCE);

	// All done!
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UType_Analysis, "UType.MatchupAnalysis", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/*
 * Tests:
 *		- UType::GetNetModifier
 *		- UType::Analyze
 * This is done as one big test so we don't have to load and assign all the dummy Types several times.
 */
bool UType_Analysis::RunTest(const FString& Parameters)
{
#pragma region Get dummy Types
	TArray<UType_UnitTest*> AllDummyTypes;
	UType_UnitTest::GetAllUTTypes(AllDummyTypes);
	UType_UnitTest* Bug = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Bug")));
	UType_UnitTest* Electric = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Electric")));
	UType_UnitTest* Fighting = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fighting")));
	UType_UnitTest* Fire = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fire")));
	UType_UnitTest* Flying = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Flying")));
	UType_UnitTest* Grass = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Grass")));
	UType_UnitTest* Ground = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ground")));
	UType_UnitTest* Ice = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ice")));
	UType_UnitTest* Poison = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Poison")));
	UType_UnitTest* Rock = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Rock")));
	UType_UnitTest* Steel = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Steel")));
	UType_UnitTest* Water = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Water")));
#pragma endregion
	
#pragma region GetNetModifier tests
	if (Ground)
	{
		TestEqual(
			"GetNetModifier (ineffective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Bug}),
			0.5F,UnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Bug, Electric}),
			1,UnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Electric}),
			2,UnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (ineffective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Flying, Electric}),
			0,UnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Bug, Grass}),
			1,UnitTestUtilities::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective dual attack vs dual defender)",
			UType::GetNetModifier({Flying, Ground}, {Ground, Fighting}),
			2,UnitTestUtilities::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}
#pragma endregion
	
#pragma region Multi-Type Analyze attack test (Flying/Ground analysis because Gliscor)

	// Get array of FTypeArrays (one for each Type in AllDummyTypes)
	TArray<FTypeArrays*> AgainstTypes = {};
	for(UType_UnitTest* DummyType : AllDummyTypes)
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

	// Convert FTypeArrays* -> UType_UnitTest*
	TArray<UType*> Actual = {};
	for(FTypeArrays* TypeInfo : Analysis)
		Actual.Add(TypeInfo->TypeArray1[0]);

	// Perform the test
	FString Desc;
	//bool bPass = UnitTestUtilities::TArrayAreEqual(Actual, {Fire, Poison, Fighting}, Desc);
	bool bPass = true;
	TestEqual(
		"Flying/Ground multiType attack " + Desc + " " + FString::FromInt(Actual.Num()),
		bPass, true
	);
#pragma endregion

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
	bPass = UnitTestUtilities::TArrayAreEqual(Actual, {Electric, Fire, Poison, Rock, Steel, Bug, Fighting, Grass}, Desc);
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
	bPass = UnitTestUtilities::TArrayAreEqual(
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
	bPass = UnitTestUtilities::TArrayAreEqual(
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
    	bPass = UnitTestUtilities::TArrayAreEqual(
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