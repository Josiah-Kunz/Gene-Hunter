/**
 * Tests an "Adamant nature" (a la Pokemon): +10% PhA | -10% SpA
 */

#pragma once

#include "MathUtil.h"
#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Delegates_RecalculateStats,
	"__GeneHunter.Effects.Delegate Tests.Recalculate Stats (\"Adamant\")",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Delegates_RecalculateStats::RunTest(const FString& Parameters)
{

	return false;

	//todo

	/*
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get baseline
	StatsComponent->RecalculateStats(true);
	const float OriginalPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float OriginalSpA = StatsComponent->GetStat(EStatEnum::SpecialAttack).GetCurrentValue();
	
	// Define "adamant" delegate (+10% PhA/-10% SpA)
	UCombatStatsComponent::FRecalculateStatsDelegate AdamantRecalculateDelegate;
	AdamantRecalculateDelegate.BindLambda([StatsComponent](EStatEnum Stat, bool bResetCurrent)
	{

		// +10% PhA
		if ( StatsComponent->GetStat(Stat).Name() == StatsComponent->GetStat(EStatEnum::PhysicalAttack).Name())
		{
			StatsComponent->GetStat(Stat).ModifyValue(10, EStatValueType::Permanent, EModificationMode::AddPercentage);
			if (bResetCurrent)
				StatsComponent->GetStat(Stat).ModifyValue(10, EStatValueType::Current, EModificationMode::AddPercentage);
		}

		// -10% SpA
		if ( StatsComponent->GetStat(Stat).Name() == StatsComponent->GetStat(EStatEnum::SpecialAttack).Name())
		{
			StatsComponent->GetStat(Stat).ModifyValue(-10, EStatValueType::Permanent, EModificationMode::AddPercentage);
			if (bResetCurrent)
				StatsComponent->GetStat(Stat).ModifyValue(-10, EStatValueType::Current, EModificationMode::AddPercentage);
		}
			
	});
	StatsComponent->AfterRecalculateStatsArray.Add(AdamantRecalculateDelegate);

	// Recalculate stats
	StatsComponent->RecalculateStats(true);

	// Check PhA
	const float ExpectedPhA = OriginalPhA * 1.1f;
	TestTrue(FString::Printf(TEXT("Increase PhA by 10 percent?: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(ExpectedPhA),
		*FString::SanitizeFloat(StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue())),
	FMathf::Abs(ExpectedPhA - StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);

	// Check SpA
	const float ExpectedSpA = OriginalSpA * 0.9f;
	TestTrue(FString::Printf(TEXT("Decrease SpA by 10 percent?: Original [%s] | Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(OriginalSpA),
		*FString::SanitizeFloat(ExpectedSpA),
		*FString::SanitizeFloat(StatsComponent->GetStat(EStatEnum::SpecialAttack).GetCurrentValue())),
	FMathf::Abs(ExpectedSpA - StatsComponent->GetStat(EStatEnum::SpecialAttack).GetCurrentValue())
		< UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
	*/
}