#pragma once

#include "AddHasteOnRecalculate_UNITTEST.h"
#include "ComponentUtilities.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecalculateStats,
                                 "__GeneHunter.Effects.Outlets.UCombatStatsComponent.RecalculateStats",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRecalculateStats::RunTest(const FString& Parameters)
{

	// Set up a dummy
	DUMMY_TEST_COMPONENT(UCombatStatsComponent, StatsComponent);

	// Update to "this" level (probably level 1? doesn't matter)
	StatsComponent->RecalculateStats();

	// Get original
	const float OriginalHaste = StatsComponent->GetStat(EStatEnum::Haste).GetValue(EStatValueType::Current);
	const float OriginalPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetValue(EStatValueType::Current);
	
	// Attach effect
	ADD_NEW_COMPONENT(UAddHasteOnRecalculate_UNITTEST, Effect, DummyActor);

	// It shouldn't do anything yet
	float CurrentHaste = StatsComponent->GetStat(EStatEnum::Haste).GetValue(EStatValueType::Current);
	TestEqual(
			FString::Printf(
			TEXT("Attached effect, but it shouldn't have done anything yet: Original [%s] | Current [%s]"),
				*FString::SanitizeFloat(OriginalHaste),
				*FString::SanitizeFloat(CurrentHaste)
			),
			CurrentHaste,
			OriginalHaste,
			0.5f);

	// Recalulating the stats should only affect Haste
	StatsComponent->RecalculateStats();
	const float CurrentPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetValue(EStatValueType::Current);
	TestEqual(
			FString::Printf(
			TEXT("Effect shouldn't affect PhA: Original [%s] | Current [%s]"),
				*FString::SanitizeFloat(OriginalPhA),
				*FString::SanitizeFloat(CurrentPhA)
			),
			CurrentPhA,
			OriginalPhA,
			0.5f);

	// Check Haste (should be affected)
	CurrentHaste = StatsComponent->GetStat(EStatEnum::Haste).GetValue(EStatValueType::Current);
	TestEqual(
			FString::Printf(
			TEXT("Haste should be increased by [+%s]: Original [%s] | Expected [%s] | Got [%s]"),
				*FString::SanitizeFloat(Effect->HasteIncrease),
				*FString::SanitizeFloat(OriginalHaste),
				*FString::SanitizeFloat(OriginalHaste + Effect->HasteIncrease),
				*FString::SanitizeFloat(CurrentHaste)
			),
			CurrentHaste,
			OriginalHaste + Effect->HasteIncrease,
			0.5f);
	
	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

