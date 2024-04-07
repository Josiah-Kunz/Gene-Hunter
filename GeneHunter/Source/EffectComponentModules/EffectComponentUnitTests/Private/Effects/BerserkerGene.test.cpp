

#pragma once

#include "ComponentUtilities.h"
#include "CombatStatUnitTestUtilities.h"
#include "BerserkerGene.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_BerserkerGene,
	"__GeneHunter.Effects.Component Tests.Berserker Gene",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_BerserkerGene::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Get original
	const float OriginalPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float OriginalPhD = StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetCurrentValue();
	const float OriginalSpD = StatsComponent->GetStat(EStatEnum::SpecialDefense).GetCurrentValue();

	// Attach BerserkerGene
	UBerserkerGene* BerserkerGene;
	ADD_COMPONENT(UBerserkerGene, BerserkerGene, DummyActor);

	// Get actual
	const float ActualPhA = StatsComponent->GetStat(EStatEnum::PhysicalAttack).GetCurrentValue();
	const float ActualPhD = StatsComponent->GetStat(EStatEnum::PhysicalDefense).GetCurrentValue();
	const float ActualSpD = StatsComponent->GetStat(EStatEnum::SpecialDefense).GetCurrentValue();

	// Get expected
	const float ExpectedPhA = OriginalPhA * (1+BerserkerGene->PermStatMod->StatMods[0].Modification /100);
	const float ExpectedPhD = OriginalPhD * (1+BerserkerGene->PermStatMod->StatMods[1].Modification/100);
	const float ExpectedSpD = OriginalSpD * (1+BerserkerGene->PermStatMod->StatMods[2].Modification/100);

	// Test PhA
	const bool bPhA = FMath::Abs(ExpectedPhA - ActualPhA) < UStatUnitTestUtilities::TOLERANCE;
	if (!bPhA)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhA was modified incorrectly: Original [%s] | Expected [%s] | Actual [%s]"),
					*FString::SanitizeFloat(OriginalPhA),
					*FString::SanitizeFloat(ExpectedPhA),
					*FString::SanitizeFloat(ActualPhA)
					)
			
	}

	// Test PhD
	const bool bPhD = FMath::Abs(ExpectedPhD - ActualPhD) < UStatUnitTestUtilities::TOLERANCE;
	if (!bPhD)
	{
		UE_LOG(LogTemp, Warning, TEXT("PhD was modified incorrectly: Original [%s] | Expected [%s] | Actual [%s]"),
					*FString::SanitizeFloat(OriginalPhD),
					*FString::SanitizeFloat(ExpectedPhD),
					*FString::SanitizeFloat(ActualPhD)
					)
	}

	// Test SpD
	const bool bSpD = FMath::Abs(ExpectedSpD - ActualSpD) < UStatUnitTestUtilities::TOLERANCE;
	if (!bSpD)
	{
		UE_LOG(LogTemp, Warning, TEXT("SpD was modified incorrectly: Original [%s] | Expected [%s] | Actual [%s]"),
				*FString::SanitizeFloat(OriginalSpD),
				*FString::SanitizeFloat(ExpectedSpD),
				*FString::SanitizeFloat(ActualSpD)
			)
	}
	 
	// Return
	BASESTATS_GC
	return bPhA && bPhD && bSpD;
}