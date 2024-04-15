#pragma once

#include "AddHasteOnRecalculate_UNITTEST.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"		// For ADD_COMPONENT macro
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
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
	if (!ComponentUtilities::AreTheSame(CurrentHaste, OriginalHaste))
	{
		UE_LOG(LogTemp, Warning,
				TEXT("Attached effect, but it shouldn't have done anything yet: Original [%s] | Current [%s]"),
					*FString::SanitizeFloat(OriginalHaste),
					*FString::SanitizeFloat(CurrentHaste)
		)
		return false;
	}

	// Recalculating the stats should only affect Haste
	StatsComponent->RecalculateStats();
	const float CurrentPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetValue(EStatValueType::Current);
	if (!ComponentUtilities::AreTheSame(CurrentPhA, OriginalPhA))
	{
		UE_LOG(LogTemp, Warning,
				TEXT("Effect shouldn't affect PhA: Original [%s] | Current [%s]"),
					*FString::SanitizeFloat(OriginalPhA),
					*FString::SanitizeFloat(CurrentPhA)
		)
		return false;
	}

	// Check Haste (should be affected)
	CurrentHaste = StatsComponent->GetStat(EStatEnum::Haste).GetValue(EStatValueType::Current);
	const float ExpectedHaste = OriginalHaste + Effect->HasteIncrease;
	if (ComponentUtilities::AreTheSame(CurrentHaste, ExpectedHaste))
	{
		UE_LOG(LogTemp, Warning,
				TEXT("Haste should be increased by [+%s]: Original [%s] | Expected [%s] | Got [%s]"),
					*FString::SanitizeFloat(Effect->HasteIncrease),
					*FString::SanitizeFloat(OriginalHaste),
					*FString::SanitizeFloat(ExpectedHaste),
					*FString::SanitizeFloat(CurrentHaste)
		)
		return false;
	}
	
	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

