
#pragma once

#include "ComponentUtilities.h"
#include "Editor.h"
#include "MathUtil.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Actor.h"
#include "Cytotoxin.h"
#include "Misc/AutomationTest.h"

/// Need to declare first!

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Cytotoxin,
	"__GeneHunter.Effects.Component Tests.Cytotoxin",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Main test

bool UEffectComponent_Components_Cytotoxin::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 
	//GEditor->GetEditorWorldContext().SetCurrentWorld(DummyWorld);

	// Add a stats component + effect
	ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	ADD_NEW_COMPONENT(UCytotoxin, Cytotoxin, DummyActor);

	// Parameters - 1% per second for 5 seconds updating every 0.1 seconds
	const float DotTime = Cytotoxin->StartingDuration();
	constexpr float TickDuration = 0.1f;

	// Set the parameters in Regrowth
	Cytotoxin->RemainingTime = DotTime;

	// Record original
	const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage
	const float Damage = OriginalHP * 0;
	Stats->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Avoid infinite loops
	uint16 Failsafe=0;
	constexpr uint16 FailAt = 50000;
	
	// Tick the world until regrowth has removed itself
	bool bCytotoxinFinished = false;
	constexpr float Dt = TickDuration/2;
	Cytotoxin->SetTickGroup(TG_DuringPhysics);
	while (!bCytotoxinFinished && Failsafe<FailAt)
	{

		// We done?
		SEARCH_FOR_COMPONENT(UCytotoxin, Cytotoxin, DummyActor);
		bCytotoxinFinished = !Cytotoxin->IsRegistered();
		
		// Tick
		if (!bCytotoxinFinished)
		{
			Cytotoxin->TickComponent(Dt, LEVELTICK_All, nullptr);
		}
		
		// Safety first!
		Failsafe++;
		
	}

	// Did we max out?
	if (Failsafe >= FailAt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max iterations reached! Maybe Regrowth isn't ticking?"));
		return false;
	}

	// Expected value
	const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const float CurrentHPMinusOne = Stats->GetModifiedValue(
		EStatEnum::Health,
		-Cytotoxin->DPS() * TickDuration,
		EStatValueType::Current,
		Cytotoxin->Mode());
	const float SingleTick = CurrentHP - CurrentHPMinusOne;
	const float HealthPerTime = SingleTick/TickDuration;
	const float ExpectedHP = OriginalHP - Damage - HealthPerTime * DotTime;
	
	// Test
	const bool Success = FMathf::Abs(CurrentHP - ExpectedHP) < 0.5f;
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Cytotoxin healing didn't match expected! Current [%s] | Expected [%s]"),
			*FString::SanitizeFloat(CurrentHP),
			*FString::SanitizeFloat(ExpectedHP)
			);
	}

	// Garbage collect
	ComponentUtilities::DestroyDummyWorld(DummyWorld);

	// Return
	return Success;
}

#pragma endregion