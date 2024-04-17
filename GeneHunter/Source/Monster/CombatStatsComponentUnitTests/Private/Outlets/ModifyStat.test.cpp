#pragma once

#include "SoftenTheBlow_UNITTEST.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"
#include "ComponentUtilities.h"		// For ADD_COMPONENT macro
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "MathUtil.h"
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
	const float ExpectedStatValue = StatsComponent->GetModifiedValue(
		Effect->SoftenStat,					// PhA
		ModValue * Effect->SoftenAmount,	// 50% * 90%
		TargetValueType,					// Current
		Mode);								// Multiply percentage

	// Modify all stats negatively
	StatsComponent->ModifyStatsUniformly(ModValue, TargetValueType, Mode);

	// Test
	const float CurrentValue = StatsComponent->GetStat(Effect->SoftenStat).GetValue(TargetValueType);
	const bool bSuccess = FMathf::Abs(CurrentValue - ExpectedStatValue) < 0.1f;
	if (!bSuccess)
	{
		UE_LOG(LogTemp, Warning,
			
				TEXT("Modified all stats by [%s%%], except for [%s], which started out as [%s] "
					"and should have gotten modified by [%s%%] "
					"resulting in [%s], but was [%s] instead."),
					*FString::SanitizeFloat(ModValue),
					*UEnum::GetValueAsString(Effect->SoftenStat),
					*FString::SanitizeFloat(OriginalStat),
					*FString::SanitizeFloat(ModValue * Effect->SoftenAmount),
					*FString::SanitizeFloat(ExpectedStatValue),
					*FString::SanitizeFloat(CurrentValue)
		)
	}
	
	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return bSuccess;
}

