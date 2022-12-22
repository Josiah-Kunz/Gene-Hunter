/**
 * Tests the Pokemon ability "Clear Body" (no stat reductions besides health), although
 * this test is slightly different strictly speaking.
 */

#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FEffects_Delegates_ModifyStats,
	"__GeneHunter.Effects.Delegate Tests.Modify Stats (\"Clear Body\")",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FEffects_Delegates_ModifyStats::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get baseline
	StatsComponent->RecalculateStats(true);
	const float OriginalPhA = StatsComponent->PhysicalAttack.GetCurrentValue();
	const float OriginalHP = StatsComponent->Health.GetCurrentValue();
	
	// Define "clear body" delegate 
	UStatsComponent::FModifyStatDelegate ClearBodyDelegate;
	ClearBodyDelegate.BindLambda([StatsComponent](FStat* Stat, float& Value, EStatValueType& ValueType, EModificationMode& Mode)
	{

		// Determine if there is an attempted reduction in a non-HP stat. If so, set a non-modifying value.
		if (!Stat->Name().Equals(StatsComponent->Health.Name()))
		{
			switch(Mode)
			{
			case EModificationMode::AddAbsolute: case EModificationMode::AddFraction: case EModificationMode::AddPercentage:
				if (Value < 0)
					Value = 0;
				break;
			case EModificationMode::MultiplyAbsolute:
				if (Value < 1)
					Value = 1;
				break;
			case EModificationMode::MultiplyPercentage:
				if (Value < 100)
					Value = 100;
				break;
			case EModificationMode::SetDirectly:
				if (Value < Stat->GetValue(ValueType))
					Value = Stat->GetValue(ValueType);
			}
		}
	});

	// Add clear body to delegate array
	StatsComponent->BeforeModifyStatsArray.Add(ClearBodyDelegate);

	// Attempt to reduce stats by -10%
	StatsComponent->ModifyStatsUniformly(-10, EStatValueType::Current, EModificationMode::AddPercentage);

	// Check PhA
	const float ExpectedPhA = OriginalPhA;
	TestTrue(FString::Printf(TEXT("Unable to decrease PhA?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedPhA),
		*FString::SanitizeFloat(StatsComponent->PhysicalAttack.GetCurrentValue())),
	FMathf::Abs(ExpectedPhA - StatsComponent->PhysicalAttack.GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);

	// Check HP
	const float ExpectedHP = OriginalHP * 0.9f;
	TestTrue(FString::Printf(TEXT("HP decreased?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedHP),
		*FString::SanitizeFloat(StatsComponent->Health.GetCurrentValue())),
	FMathf::Abs(ExpectedHP - StatsComponent->Health.GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}