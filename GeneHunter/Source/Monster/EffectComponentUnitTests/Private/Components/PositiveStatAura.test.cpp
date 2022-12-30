/**
 * Tests a positive stat aura (a la Pokemon natures).
 */

#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "StatUnitTestUtilities.h"
#include "PositiveStatAura.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_PositiveStatAura,
	"__GeneHunter.Effects.Component Tests.Positive Stat Aura",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_PositiveStatAura::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Assign percentage
	constexpr float Percentage = 10;

	// Get expected
	const float Expected = StatsComponent->PhysicalAttack.GetPermanentValue() * (1+Percentage/100.0f);

	// Attach +PhA
	UPositiveStatAura* PlusPhA = NewObject<UPositiveStatAura>(DummyActor);
	PlusPhA->AssignData(&StatsComponent->PhysicalAttack, Percentage, EModificationMode::AddPercentage,
		EStatValueType::Permanent);
	REQUIRE_COMPONENT(UPositiveStatAura, PlusPhA, DummyActor)

	// Trigger recalculation
	StatsComponent->RecalculateStats();

	// Test that it has been so done
	const float Actual = StatsComponent->PhysicalAttack.GetCurrentValue();
	TestTrue(
		FString::Printf(TEXT("PhA was modified correctly: Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(Expected),
				*FString::SanitizeFloat(Actual)
			),
	FMath::Abs(Expected - Actual) < UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}