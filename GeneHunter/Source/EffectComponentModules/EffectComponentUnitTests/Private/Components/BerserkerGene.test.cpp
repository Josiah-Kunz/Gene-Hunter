/**
 * Tests a positive stat aura (a la Pokemon natures).
 */

#pragma once

#include "ComponentUtilities.h"
#include "StatUnitTestUtilities.h"
#include "BerserkerGene.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_BerserkerGene,
	"__GeneHunter.Effects.Component Tests.Berserker Gene",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_BerserkerGene::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get expected
	const float ExpectedPhA =StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetPermanentValue() * 1.15f;
	const float ExpectedPhD =StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetPermanentValue() * 0.9f;
	const float ExpectedSpD =StatsComponent->GetStat(EStatEnum::SpecialDefense).GetPermanentValue() * 0.9f;

	// Attach BerserkerGene
	UBerserkerGene* BerserkerGene = NewObject<UBerserkerGene>(DummyActor);
	REQUIRE_COMPONENT(UBerserkerGene, BerserkerGene, DummyActor)

	// Trigger recalculation
	StatsComponent->RecalculateStats(true);

	// Get actual
	const float ActualPhA =StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float ActualPhD =StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetCurrentValue();
	const float ActualSpD =StatsComponent->GetStat(EStatEnum::SpecialDefense).GetCurrentValue();

	// Test PhA
	TestTrue(
		FString::Printf(TEXT("PhA was modified correctly: Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(ExpectedPhA),
				*FString::SanitizeFloat(ActualPhA)
			),
	FMath::Abs(ExpectedPhA - ActualPhA) < UStatUnitTestUtilities::TOLERANCE);

	// Test PhD
	TestTrue(
		FString::Printf(TEXT("PhD was modified correctly: Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(ExpectedPhD),
				*FString::SanitizeFloat(ActualPhD)
			),
	FMath::Abs(ExpectedPhD - ActualPhD) < UStatUnitTestUtilities::TOLERANCE);

	// Test SpD
	TestTrue(
		FString::Printf(TEXT("SpD was modified correctly: Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(ExpectedSpD),
				*FString::SanitizeFloat(ActualSpD)
			),
	FMath::Abs(ExpectedSpD - ActualSpD) < UStatUnitTestUtilities::TOLERANCE);
	
	// Return
	BASESTATS_GC
	return true;
}