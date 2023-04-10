﻿#pragma once

#include "SoftenTheBlow_UNITTEST.h"
#include "ComponentUtilities.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FModifyStat,
                                 "__GeneHunter.Effects.Outlets.UCombatStatsComponent.ModifyStat",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FModifyStat::RunTest(const FString& Parameters)
{

	// Set up a dummy
	DUMMY_TEST_COMPONENT(UCombatStatsComponent, StatsComponent);
	
	// Attach effect
	ADD_NEW_COMPONENT(USoftenTheBlow_UNITTEST, Effect, DummyActor);

	// Settings
	constexpr EStatValueType TargetValueType = EStatValueType::Current;
	constexpr float ModValue = 50;
	constexpr EModificationMode Mode = EModificationMode::MultiplyPercentage;

	// Get original
	const float OriginalStat = StatsComponent->GetStat(Effect->SoftenStat).GetValue(TargetValueType);

	// We expect the target stat to not get reduced as much (e.g., not by half, but by 90% of half [40% reduction total])
	const float ExpectedStatValue = StatsComponent->GetModifiedValue(Effect->SoftenStat,
		ModValue * Effect->SoftenAmount, TargetValueType, Mode);

	// Modify all stats negatively
	StatsComponent->ModifyStatsUniformly(ModValue, TargetValueType, Mode);

	// Test
	const float CurrentValue = StatsComponent->GetStat(Effect->SoftenStat).GetValue(TargetValueType);
	TestEqual(
			FString::Printf(
			TEXT("Modified all stats by [%s%], except for [%s], which should have gotten modified by [%s%] resulting in [%s], but was [%s] instead."),
				*FString::SanitizeFloat(ModValue),
				*UEnum::GetValueAsString(Effect->SoftenStat),
				*FString::SanitizeFloat(ModValue * Effect->SoftenAmount),
				*FString::SanitizeFloat(ExpectedStatValue),
				*FString::SanitizeFloat(CurrentValue)
			),
			CurrentValue,
			ExpectedStatValue,
			0.5f);
	
	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}
