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

	UE_LOG(LogTemp, Warning, TEXT("PhA is %s | Level is %i"),
		*FString::SanitizeFloat(StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue()),
		StatsComponent->LevelComponent->GetLevel()
		)

	// Get original
	const float OriginalPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float OriginalPhD = StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetCurrentValue();
	const float OriginalSpD = StatsComponent->GetStat(EStatEnum::SpecialDefense).GetCurrentValue();

	// Get expected
	const float ExpectedPhA = OriginalPhA * (1+UBerserkerGene::PhAIncrease/100);
	const float ExpectedPhD = OriginalPhD * (1-UBerserkerGene::DefDecrease/100);
	const float ExpectedSpD = OriginalSpD * (1-UBerserkerGene::DefDecrease/100);

	// Attach BerserkerGene
	UBerserkerGene* BerserkerGene;
	ADD_COMPONENT(UBerserkerGene, BerserkerGene, DummyActor);

	// Trigger recalculation - should happen automatically
	//StatsComponent->RecalculateStats(true);
	StatsComponent->ModifyStat(EStatEnum::PhysicalAttack, 15, EStatValueType::Permanent, EModificationMode::AddPercentage);
	StatsComponent->ModifyStat(EStatEnum::PhysicalAttack, 15, EStatValueType::Current, EModificationMode::AddPercentage);

	// Get actual
	const float ActualPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float ActualPhD = StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetCurrentValue();
	const float ActualSpD = StatsComponent->GetStat(EStatEnum::SpecialDefense).GetCurrentValue();

	// Test PhA
	TestTrue(
		FString::Printf(TEXT("PhA was modified correctly: Original [%s] | Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(OriginalPhA),
				*FString::SanitizeFloat(ExpectedPhA),
				*FString::SanitizeFloat(ActualPhA)
			),
	FMath::Abs(ExpectedPhA - ActualPhA) < UStatUnitTestUtilities::TOLERANCE);

	// Test PhD
	TestTrue(
		FString::Printf(TEXT("PhD was modified correctly: Original [%s] | Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(OriginalPhD),
				*FString::SanitizeFloat(ExpectedPhD),
				*FString::SanitizeFloat(ActualPhD)
			),
	FMath::Abs(ExpectedPhD - ActualPhD) < UStatUnitTestUtilities::TOLERANCE);

	// Test SpD
	TestTrue(
		FString::Printf(TEXT("SpD was modified correctly: Original [%s] | Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(OriginalSpD),
				*FString::SanitizeFloat(ExpectedSpD),
				*FString::SanitizeFloat(ActualSpD)
			),
	FMath::Abs(ExpectedSpD - ActualSpD) < UStatUnitTestUtilities::TOLERANCE);
	 
	// Return
	BASESTATS_GC
	return true;
}