
#pragma once

#include "ComponentUtilities.h"
#include "CombatStatUnitTestUtilities.h"
#include "MathUtil.h"
#include "WoundedSoul.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_WoundedSoul,
	"__GeneHunter.Effects.Component Tests.Wounded Soul",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_WoundedSoul::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Record original
	const float OriginalHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage without effect
	const float Damage = OriginalHP * 0.4f;
	StatsComponent->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Test the damage taken
	float CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	float ExpectedHP = OriginalHP - Damage;
	const bool bTookDamage = FMathf::Abs(CurrentHP - ExpectedHP) < UStatUnitTestUtilities::TOLERANCE;
	if (!bTookDamage)
	{
		UE_LOG(LogTemp, Warning, TEXT("Damage taken (without effect) failed!: Original HP [%s] | Damage [%s] | Current HP [%s] | Expected [%s]"),
				*FString::SanitizeFloat(OriginalHP),
				*FString::SanitizeFloat(Damage),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
			);
	}

	// Attach effect
	ADD_NEW_COMPONENT(UWoundedSoul, Effect, DummyActor);
	
	// Try to heal half the damage back
	const float Heal = 0.5*Damage;
	StatsComponent->ModifyStat(EStatEnum::Health, Heal, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Test that there was 75% healing done
	CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	ExpectedHP = OriginalHP - Damage + (1-Effect->HealingReduction/100) * Heal;
	const bool bHealedCorrectly = FMathf::Abs(CurrentHP - ExpectedHP) < UStatUnitTestUtilities::TOLERANCE;
	if (!bHealedCorrectly)
	{
		UE_LOG(LogTemp, Warning, TEXT("Healing should be mitigated, but wasn't: Original HP [%s] | Damage [%s] | Attempted Healed [%s] Current HP [%s] | Expected [%s]"),
				*FString::SanitizeFloat(OriginalHP),
				*FString::SanitizeFloat(Damage),
				*FString::SanitizeFloat(Heal),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
			);
	}
	 
	// Return
	BASESTATS_GC
	return bTookDamage && bHealedCorrectly;
}