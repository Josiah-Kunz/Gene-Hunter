
#include "Type.h"
#include "Type_UnitTest.h"
#include "AITestSuite/Public/AITestsCommon.h"

class FType_UnitTests
{
public:
	constexpr static float TOLERANCE = 0.1F;
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UType_CombineModifiers, "UType.CombineModifiers", EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UType_CombineModifiers::RunTest(const FString& Parameters)
{

	// Heals
	TestEqual("-1 & 2", UType::CombineModifiers(-1, 2), -0.5F, FType_UnitTests::TOLERANCE);
	TestEqual("-1 & 1", UType::CombineModifiers(-1, 1), -1, FType_UnitTests::TOLERANCE);
	TestEqual("-1 & 0.5", UType::CombineModifiers(-1, 0.5), -1, FType_UnitTests::TOLERANCE);
	TestEqual("-1 & 0", UType::CombineModifiers(-1, 0), -1, FType_UnitTests::TOLERANCE);
	TestEqual("-1 & -1", UType::CombineModifiers(-1, -1), -1, FType_UnitTests::TOLERANCE);

	// Immune
	TestEqual("0 & -1", UType::CombineModifiers(0, -1), -1, FType_UnitTests::TOLERANCE);
	TestEqual("0 & 0", UType::CombineModifiers(0, 0), 0, FType_UnitTests::TOLERANCE);
	TestEqual("0 & 0.5", UType::CombineModifiers(0, 0.5), 0, FType_UnitTests::TOLERANCE);
	TestEqual("0 & 1", UType::CombineModifiers(0, 1), 0, FType_UnitTests::TOLERANCE);
	TestEqual("0 & 2", UType::CombineModifiers(0, 2), 0, FType_UnitTests::TOLERANCE);

	// Resist
	TestEqual("0.5 & -1", UType::CombineModifiers(0.5, -1), -1, FType_UnitTests::TOLERANCE);
	TestEqual("0.5 & 0", UType::CombineModifiers(0.5, 0), 0, FType_UnitTests::TOLERANCE);
	TestEqual("0.5 & 0.5", UType::CombineModifiers(0.5, 0.5), 0.25F, FType_UnitTests::TOLERANCE);
	TestEqual("0.5 & 1", UType::CombineModifiers(0.5, 1), 0.5F, FType_UnitTests::TOLERANCE);
	TestEqual("0.5 & 2", UType::CombineModifiers(0.5, 2), 1, FType_UnitTests::TOLERANCE);

	// Neutral
	TestEqual("1 & -1", UType::CombineModifiers(1, -1), -1, FType_UnitTests::TOLERANCE);
	TestEqual("1 & 0", UType::CombineModifiers(1, 0), 0, FType_UnitTests::TOLERANCE);
	TestEqual("1 & 0.5", UType::CombineModifiers(1, 0.5), 0.5F, FType_UnitTests::TOLERANCE);
	TestEqual("1 & 1", UType::CombineModifiers(1, 1), 1, FType_UnitTests::TOLERANCE);
	TestEqual("1 & 2", UType::CombineModifiers(1, 2), 2, FType_UnitTests::TOLERANCE);
	
	// Weak
	TestEqual("2 & -1", UType::CombineModifiers(2, -1), -0.5F, FType_UnitTests::TOLERANCE);
	TestEqual("2 & 0", UType::CombineModifiers(2, 0), 0, FType_UnitTests::TOLERANCE);
	TestEqual("2 & 0.5", UType::CombineModifiers(2, 0.5), 1, FType_UnitTests::TOLERANCE);
	TestEqual("2 & 1", UType::CombineModifiers(2, 1), 2, FType_UnitTests::TOLERANCE);
	TestEqual("2 & 2", UType::CombineModifiers(2, 2), 4, FType_UnitTests::TOLERANCE);

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
	UType_UnitTest* Flying = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Flying")));
	UType_UnitTest* Ground = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ground")));
	UType_UnitTest* Bug = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Bug")));
	UType_UnitTest* Grass = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Grass")));
	UType_UnitTest* Electric = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Electric")));
	UType_UnitTest* Fire = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fire")));
	UType_UnitTest* Fighting = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fighting")));
	UType_UnitTest* Poison = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Poison")));
	UType_UnitTest* Rock = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Rock")));
	UType_UnitTest* Steel = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Steel")));
#pragma endregion
	
#pragma region GetNetModifier tests
	if (Ground)
	{
		TestEqual(
			"GetNetModifier (ineffective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Bug}),
			0.5F, FType_UnitTests::TOLERANCE);
		TestEqual(
			"GetNetModifier (neutral single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Bug, Electric}),
			1, FType_UnitTests::TOLERANCE);
		TestEqual(
			"GetNetModifier (effective single attack vs dual defender)",
			UType::GetNetModifier({Ground}, {Fighting, Electric}),
			2, FType_UnitTests::TOLERANCE);
	} else
	{
		TestEqual("Type [Ground] is null!", true, false);
	}
#pragma endregion
	
#pragma region Analysis tests (Flying/Ground analysis because Gliscor)

	// Get the UTypes (actual)
	TArray EffectiveMultiAtk_UType = UType::Analyze(
			{Ground, Flying},
			TArray<UType*>(AllDummyTypes),
			FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
				EAttackModifierMode::MultiType,
				true
			);

	// Convert to UType_UnitTest (actual; and start building description in case it fails)
	FString Desc = "[Actual: ";
	TArray<UType_UnitTest*> EffectiveMultiAtk_Actual;
	for(UType* Type : EffectiveMultiAtk_UType)
	{
		if (UType_UnitTest* UTType = Cast<UType_UnitTest>(Type))
		{
			EffectiveMultiAtk_Actual.Add(UTType);
			Desc += UTType->GetName() + " ";
		}
	}

	// Get expected result
	const TArray EffectiveMultiAtk_Expected = {Fire, Poison, Fighting};
	Desc += "// Expected: ";
	for(UType_UnitTest* UTType : EffectiveMultiAtk_Expected)
		Desc += UTType->GetName() + " ";
	Desc += "]";
	Desc = Desc.Replace(TEXT(" ]"), TEXT("]"));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = EffectiveMultiAtk_Expected.Num() == EffectiveMultiAtk_Actual.Num();
	if (bPass)
	{
		for(UType_UnitTest* UTType : EffectiveMultiAtk_Expected)
		{
			if (!EffectiveMultiAtk_Actual.Contains(UTType))
			{
				Desc += " " + UTType->GetName() + " not found!";
				bPass = false;
				break;
			}
		}
	} else
	{
		Desc += " " + FString::SanitizeFloat(EffectiveMultiAtk_Expected.Num()) + " != " + FString::SanitizeFloat(EffectiveMultiAtk_Actual.Num());
	}

	// Perform the test
	TestEqual(
		"Flying/Ground multiType attack " + Desc,
		bPass, true
	);
#pragma endregion
	/*
	TestSame(
    		"Flying/Ground coverage",
    		UType::Analyze(
    			{Ground, Flying},
    			FFloatRange{
    			FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
    				},
    				EAttackModifierMode::Coverage,
    				true
    			),
    			{Electric, Fire, Poison, Rock, Steel, Bug, Fighting, Grass}
    	);
*/
	// All passed!
	return true;
}