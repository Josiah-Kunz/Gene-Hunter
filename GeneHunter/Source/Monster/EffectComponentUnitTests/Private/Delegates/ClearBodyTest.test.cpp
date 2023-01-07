/**
 * Tests the Pokemon ability "Clear Body" (no stat reductions besides health), although
 * this test is slightly different strictly speaking.
 */

#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Delegates_ModifyStats,
	"__GeneHunter.Effects.Delegate Tests.Modify Stats (\"Clear Body\")",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Delegates_ModifyStats::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get baseline
	StatsComponent->RecalculateStats(true);
	const float OriginalPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float OriginalHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	
	// Define "clear body" delegate 
	UStatsComponent::FModifyStatDelegate ClearBodyDelegate;
	ClearBodyDelegate.BindLambda([StatsComponent](EStatEnum Stat, float& Value, EStatValueType& ValueType, EModificationMode& Mode)
	{
		

		// Determine if there is an attempted reduction in a non-HP stat. If so, set a non-modifying value.
		if (Stat != EStatEnum::Health)
			StatsComponent->AvertReduction(Stat, Value, ValueType, Mode);
	});

	// Add clear body to delegate array
	StatsComponent->BeforeModifyStatArray.Add(ClearBodyDelegate);

	// Attempt to reduce stats by -10%
	StatsComponent->ModifyStatsUniformly(-10, EStatValueType::Current, EModificationMode::AddPercentage);

	// Check PhA
	const float ExpectedPhA = OriginalPhA;
	TestTrue(FString::Printf(TEXT("Unable to decrease PhA?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedPhA),
		*FString::SanitizeFloat(StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue())),
	FMathf::Abs(ExpectedPhA - StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);

	// Check HP
	const float ExpectedHP = OriginalHP * 0.9f;
	TestTrue(FString::Printf(TEXT("HP decreased?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedHP),
		*FString::SanitizeFloat(StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue())),
	FMathf::Abs(ExpectedHP - StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}