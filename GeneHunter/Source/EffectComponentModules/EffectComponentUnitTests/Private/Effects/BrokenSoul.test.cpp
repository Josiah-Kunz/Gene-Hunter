
#pragma once

#include "BrokenSoul.h"
#include "ComponentUtilities.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Actor.h"
#include "MathUtil.h"
#include "Misc/AutomationTest.h"
#include "Regrowth.h"
#include "WoundedSoul.h"

/// Need to declare first!

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_BrokenSoul,
	"__GeneHunter.Effects.Component Tests.Broken Soul",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Main test

bool UEffectComponent_Components_BrokenSoul::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 

	// Add a stats component + effect
	ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	ADD_NEW_COMPONENT(UBrokenSoul, BrokenSoul, DummyActor);

	// Record original parameters
	const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	constexpr float ReductionMult = 1-BrokenSoul->HealingReduction/100;

	// Take Damage Test
	// ================
	
	// Take damage
	const float Damage = OriginalHP * 0.9f;
	Stats->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Make sure we took damage correctly (BrokenSoul should only affect *healing*)
	float ExpectedHP = OriginalHP - Damage;
	float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const bool bTookDamage = FMathf::Abs(CurrentHP - ExpectedHP) < 0.1f;
	if (!bTookDamage)
	{
		UE_LOG(LogTemp, Warning, TEXT("BrokenSoul modified damage (should only modify healing):"
				" Current [%s] | Expected [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
				)

		// Don't run the other tests, as they will fail
		return false;
	}

	// Big Heal Test
	// =============

	// Test big healing reduction
	const float BigHeal = 0.25f * OriginalHP;
	Stats->ModifyStat(EStatEnum::Health, BigHeal, EStatValueType::Current, EModificationMode::AddAbsolute);
	ExpectedHP = OriginalHP - Damage + BigHeal*ReductionMult;
	CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const bool bReducedBigHeal = FMathf::Abs(CurrentHP - ExpectedHP) < 0.1f;
	if (!bReducedBigHeal){
		UE_LOG(LogTemp, Warning, TEXT("BrokenSoul didn't reduce a big heal:"
				" Current [%s] | Expected [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP)
				)

		// Don't run the other tests, as they will fail
		return false;
	}
	
	// Avoid infinite loops
	uint16 Failsafe = 0;
	constexpr uint16 FailAt = 50000;

	// HoT Test
	// ========

	// Add Regrowth
	ADD_NEW_COMPONENT(URegrowth, Regrowth, DummyActor)

	// Get parameters (we'll use these later---trust me)
	const float TickDuration = Regrowth->TickDuration();

	// Units: %/sec * sec/tick * TotalHP/100% = HP/tick
	const float TickHeal = Regrowth->HPS() * TickDuration * OriginalHP/100;
	
	// Tick the world a few ticks
	const float Dt = TickDuration/2;
	Regrowth->SetTickGroup(TG_DuringPhysics);
	const float TotalTime = FMathf::Min(Regrowth->RemainingTime, BrokenSoul->RemainingTime)/2;
	bool bReducedHoT = false;
	for(float Time = Dt; Time < TotalTime; Time += Dt){

		// Time to tick?
		if (Regrowth->RemainingTime - Dt <= Regrowth->NextModTime)
		{
			ExpectedHP += TickHeal * ReductionMult;
		}
		
		// Attempt to tick
		Regrowth->TickComponent(Dt, LEVELTICK_All, nullptr);
		
		// Safety first!
		Failsafe++;
		if (Failsafe > FailAt)
		{
			UE_LOG(LogTemp, Warning, TEXT("Ticking the HoT took too long! Maybe Dt is zero? Dt = [%s] | Ending..."),
				*FString::SanitizeFloat(Dt)
				)
			return false;
		}

		// Test it's what we expect
		CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
		bReducedHoT = FMathf::Abs(CurrentHP - ExpectedHP) < 0.01f;
		if (!bReducedHoT)
		{
			UE_LOG(LogTemp, Warning, TEXT("BrokenSoul didn't reduce the HoT correctly:"
				" Current [%s] | Expected [%s] | Time: [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP),
				*FString::SanitizeFloat(Time)
				)

			// We'll let it run because it could be useful to see the numbers over time
		}
		
	}

	// Results
	if (!bReducedHoT)
	{
		return false;
	}

	// Remove Regrowth
	Regrowth->DestroyComponent();

	// Stacks with WoundedSoul Test
	// ============================
	
	// Add component
	ADD_NEW_COMPONENT(UWoundedSoul, WoundedSoul, DummyActor)

	// Get parameters
	constexpr float WoundedMult = 1-WoundedSoul->HealingReduction/100;

	// Try to heal
	const float FinalHeal = OriginalHP - Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	Stats->ModifyStat(EStatEnum::Health, FinalHeal, EStatValueType::Current, EModificationMode::AddAbsolute);
	
	// Check
	CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	ExpectedHP += FinalHeal * ReductionMult * WoundedMult;
	if (FMathf::Abs(CurrentHP - ExpectedHP) >= 0.01f)
	{
		UE_LOG(LogTemp, Warning, TEXT("WoundedSoul and BrokenSoul didn't stack correctly!"
			" Current [%s] | Expected [%s]"),
			*FString::SanitizeFloat(CurrentHP),
			*FString::SanitizeFloat(ExpectedHP)
			)
		return false;
	}
	
	// Cleanup
	// =======

	// Garbage collect
	ComponentUtilities::DestroyDummyWorld(DummyWorld);

	// Return
	return true;
}

#pragma endregion