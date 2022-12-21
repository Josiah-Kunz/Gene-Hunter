#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsComponent_Delegates_AdamantTest,
	"__GeneHunter.FStat.StatsComponent.Delegates.\"Adamant\" Test",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsComponent_Delegates_AdamantTest::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get baseline
	const float OriginalPhA = StatsComponent->PhysicalAttack.GetCurrentValue();
	const float OriginalSpA = StatsComponent->SpecialAttack.GetCurrentValue();
	
	// Define "adamant" delegate (+10% PhA/-10% SpA)
	UStatsComponent::FRecalculateStatDelegate Adamant;
	Adamant.BindLambda([StatsComponent](FStat* Stat, float Value, EStatValueType ValueType, EModificationMode Mode)
	{

		// +10% PhA
		if ( Stat->Name() == StatsComponent->PhysicalAttack.Name())
			Stat->ModifyValue(10, EStatValueType::Current, EModificationMode::AddPercentage);

		// -10% SpA
		if ( Stat->Name() == StatsComponent->SpecialAttack.Name())
			Stat->ModifyValue(-10, EStatValueType::Current, EModificationMode::AddPercentage);
		
			
	});
	StatsComponent->AfterRecalculateStatsArray.Add(Adamant);

	// Recalculate stats
	StatsComponent->RecalculateStats();

	// Check PhA
	const float ExpectedPhA = OriginalPhA * 1.1f;
	TestTrue(FString::Printf(TEXT("Increase PhA by 10 percent?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedPhA),
		*FString::SanitizeFloat(StatsComponent->PhysicalAttack.GetCurrentValue())),
	FMathf::Abs(ExpectedPhA - StatsComponent->PhysicalAttack.GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);
	
	
	// Return
	BASESTATS_GC
	return true;
}