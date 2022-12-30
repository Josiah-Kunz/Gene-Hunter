/**
 * Tests that the delegates make it to their delegate arrays when an EffectComponent is attached.
 */

#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "StatUnitTestUtilities.h"
#include "PositiveStatAura.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Attachment,
	"__GeneHunter.Effects.Component Tests.Attachment",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Attachment::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Attach an effect
	UPositiveStatAura* StatModifier = nullptr;
	REQUIRE_COMPONENT(UPositiveStatAura, StatModifier, DummyActor)

	// Test that it auto recognized StatsComponent
	TestTrue(FString::Printf(TEXT("EffectComponent found StatsComponent automatically?")),
	StatModifier->StatsComponent != nullptr);

	// Test RecalculateStats number of delegates
	constexpr int RecalculateExpected = 1;
	TestTrue(FString::Printf(TEXT("Delegates in RecalculateStats: Expected [%s] vs Actual [%s]"),
		*FString::SanitizeFloat(RecalculateExpected),
		*FString::SanitizeFloat(StatsComponent->AfterRecalculateStatsArray.Num())),
	FMathf::Abs(RecalculateExpected - StatsComponent->AfterRecalculateStatsArray.Num())
		< UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}