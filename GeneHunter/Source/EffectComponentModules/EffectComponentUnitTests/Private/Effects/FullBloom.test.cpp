
#pragma once

#include "ComponentUtilities.h"
#include "Editor.h"
#include "MathUtil.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Actor.h"
#include "FullBloom.h"
#include "Misc/AutomationTest.h"

/// Need to declare first!

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_FullBloom,
	"__GeneHunter.Effects.Component Tests.FullBloom",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Main test

bool UEffectComponent_Components_FullBloom::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 
	//GEditor->GetEditorWorldContext().SetCurrentWorld(DummyWorld);

	// Add a stats component + effect
	ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	ADD_NEW_COMPONENT(UFullBloom, FullBloom, DummyActor);

	// Parameters - 1% per second for 5 seconds updating every 0.1 seconds
	constexpr float HotTime = 5;

	// Set the parameters in FullBloom
	FullBloom->RemainingTime = HotTime;

	// Record original
	const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage
	const float Damage = OriginalHP * 0.5f;
	Stats->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Avoid infinite loops
	uint16 Failsafe=0;
	constexpr uint16 FailAt = 50000;
	
	// Tick the world until FullBloom has removed itself
	bool bFullBloomFinished = false;
	const float Dt = FullBloom->TickDuration()/2;
	FullBloom->SetTickGroup(TG_DuringPhysics);
	while (!bFullBloomFinished && Failsafe<FailAt)
	{

		// We done?
		SEARCH_FOR_COMPONENT(UFullBloom, FullBloom, DummyActor);
		bFullBloomFinished = FullBloom == nullptr || !FullBloom->IsRegistered();
		
		// Tick
		if (!bFullBloomFinished)
		{
			FullBloom->TickComponent(Dt, LEVELTICK_All, nullptr);
		}
		
		// Safety first!
		Failsafe++;
		
	}

	// Did we max out?
	if (Failsafe >= FailAt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max iterations reached! Maybe FullBloom isn't ticking?"));
		return false;
	}

	// Expected value
	const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const float CurrentHPPlusOne = Stats->GetModifiedValue(
		EStatEnum::Health,
		FullBloom->HPS() * FullBloom->TickDuration(),
		EStatValueType::Current,
		FullBloom->Mode());
	const float SingleTick = CurrentHPPlusOne - CurrentHP;
	const float HealthPerTime = SingleTick/FullBloom->TickDuration();
	const float ExpectedHP = OriginalHP - Damage + HealthPerTime * HotTime;
	
	// Test
	const bool Success = FMathf::Abs(CurrentHP - ExpectedHP) < 0.5f;
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("FullBloom healing didn't match expected! Current [%s] | Expected [%s]"),
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