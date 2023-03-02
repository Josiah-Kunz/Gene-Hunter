
#pragma once

#include "ComponentUtilities.h"
#include "CombatStatUnitTestUtilities.h"
#include "Invulnerable.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Invulnerable,
	"__GeneHunter.Effects.Component Tests.Invulnerable",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Invulnerable::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Record original
	const float OriginalHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage without effect
	const float Damage = OriginalHP * 0.5f;
	StatsComponent->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Test the damage taken
	float CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	float ExpectedHP = OriginalHP - Damage;
	TestEqual(
		FString::Printf(TEXT("Damage taken (without effect) failed!: Original HP [%s] | Damage [%s] | Current HP [%s] | Expected [%s]"),
				*FString::SanitizeFloat(OriginalHP),
				*FString::SanitizeFloat(Damage),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
			),
			CurrentHP,
			ExpectedHP,
			UStatUnitTestUtilities::TOLERANCE);

	// Attach effect
	ADD_NEW_COMPONENT(UInvulnerable, Effect, DummyActor);
	
	// Try to take damage againe
	StatsComponent->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Test that there was no change
	CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	ExpectedHP = OriginalHP - Damage; // Not 2x damage
	TestEqual(
		FString::Printf(TEXT("There shouldn't be any damage taken again (but there was!): Original HP [%s] | Damage (again) [%s] | Current HP [%s] | Expected [%s]"),
				*FString::SanitizeFloat(OriginalHP),
				*FString::SanitizeFloat(Damage),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
			),
			CurrentHP,
			ExpectedHP,
			UStatUnitTestUtilities::TOLERANCE);

	// Test that we can heal tho
	StatsComponent->ModifyStat(EStatEnum::Health, Damage, EStatValueType::Current, EModificationMode::AddAbsolute);
	CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	ExpectedHP = OriginalHP;
	TestEqual(
		FString::Printf(TEXT("We should still be able to heal even tho invulnerable: Original HP [%s] | Current HP [%s] | Expected [%s]"),
				*FString::SanitizeFloat(OriginalHP),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
			),
			CurrentHP,
			ExpectedHP,
			UStatUnitTestUtilities::TOLERANCE);
	 
	// Return
	BASESTATS_GC
	return true;
}