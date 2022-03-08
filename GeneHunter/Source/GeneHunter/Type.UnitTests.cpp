
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

bool UType_Analysis::RunTest(const FString& Parameters)
{
	// Get dummy Types
	TArray<UType_UnitTest*> AllDummyTypes;
	UType_UnitTest::GetAllUTTypes(AllDummyTypes);
	UType_UnitTest* Flying = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Flying")));
	UType_UnitTest* Ground = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ground")));
	UType_UnitTest* Bug = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Bug")));
	UType_UnitTest* Grass = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Grass")));
	UType_UnitTest* Electric = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Electric")));
	UType_UnitTest* Fire = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fire")));
	UType_UnitTest* Fighting = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fighting")));

	// GetNetModifier tests
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
	/*

	// Analyze attack
	TestSame("Analyze attack (non-resisted)",
		UType::Analyze(
			{&Fire, &Earth},
			FFloatRange{
				FFloatRangeBound::Inclusive(1),
				FFloatRangeBound::Open()
				},
			EAttackModifierMode::Coverage,
			true),
		AllTypes);
	TestSame("Analyze attack (only advantage)",
		UType::Analyze(
			{&Fire, &Earth},
			FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
			EAttackModifierMode::Coverage,
			true),
		{&Air, &Water});

	// Analyze defense
	TestSame("Analyze defense (non-weak)",
		UType::Analyze(
			{&Air, &Earth},
			FFloatRange{
				FFloatRangeBound::Open(),
				FFloatRangeBound::Inclusive(1)
				},
			EAttackModifierMode::Coverage,
			false),
			{&Earth, &Water}
		);

	// Analyze Pokemon attacks: "Gliscor" (my personal favorite Pokemon)
	//	Note: only relevant types are set up
	UType Ground, Flying, Bug, Grass, Electric, Poison, Rock, Steel, Ice, Fighting;
	Ground.AttackModifiers = {
		{&Flying, FAttackModifier{0}},
		{&Bug, FAttackModifier{0.5F}},
		{&Grass, FAttackModifier{0.5F}},
		{&Electric, FAttackModifier{2}},
		{&Fire, FAttackModifier{2}},
		{&Poison, FAttackModifier{2}},
		{&Rock, FAttackModifier{2}},
		{&Steel, FAttackModifier{2}},
};
	Flying.AttackModifiers = {
		{&Electric, FAttackModifier{0.5F}},
		{&Rock, FAttackModifier{0.5F}},
		{&Steel, FAttackModifier{0.5F}},
		{&Bug, FAttackModifier{2}},
		{&Fighting, FAttackModifier{2}},
		{&Grass, FAttackModifier{2}},
	};
	Electric.AttackModifiers = {
		{&Ground, FAttackModifier{0}},
		{&Flying, FAttackModifier{2}}
	};
	Rock.AttackModifiers = {
		{&Flying, FAttackModifier{2}},
		{&Ground, FAttackModifier{0.5F}},
	};
	Ice.AttackModifiers = {
		{&Flying, FAttackModifier{2}},
		{&Ground, FAttackModifier{2}},
	};
	Bug.AttackModifiers = {
		{&Flying, FAttackModifier{0.5F}}
	};
	Fighting.AttackModifiers = {
		{&Flying, FAttackModifier{0.5F}}
	};
	Grass.AttackModifiers = {
		{&Flying, FAttackModifier{0.5F}},
		{&Ground, FAttackModifier{2}},
	};
	Poison.AttackModifiers = {
		{&Ground, FAttackModifier{0.5F}}
	};
	Water.AttackModifiers = {
		{&Ground, FAttackModifier{2}},
	};

	// Execute Flying/Ground analysis
	TestSame(
		"Flying/Ground multiType attack",
		UType::Analyze(
			{&Ground, &Flying},
			FFloatRange{
				FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
				},
				EAttackModifierMode::MultiType,
				true
			),
			{&Fire, &Poison, &Flying}
	);
	TestSame(
    		"Flying/Ground coverage",
    		UType::Analyze(
    			{&Ground, &Flying},
    			FFloatRange{
    			FFloatRangeBound::Exclusive(1),
				FFloatRangeBound::Open()
    				},
    				EAttackModifierMode::Coverage,
    				true
    			),
    			{&Electric, &Fire, &Poison, &Rock, &Steel, &Bug, &Fighting, &Grass, &Air}
    	);
    	*/

	// All passed!
	return true;
}