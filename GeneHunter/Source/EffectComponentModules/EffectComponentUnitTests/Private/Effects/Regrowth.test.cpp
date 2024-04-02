
#pragma once

#include "ComponentUtilities.h"
#include "Editor.h"
#include "MathUtil.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Actor.h"
#include "Regrowth.h"
#include "TimedEffectComponent.h"
#include "Misc/AutomationTest.h"

/// Need to declare first!

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Regrowth,
	"__GeneHunter.Effects.Component Tests.Regrowth",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Main test

bool UEffectComponent_Components_Regrowth::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 
	//GEditor->GetEditorWorldContext().SetCurrentWorld(DummyWorld);








	// Add a stats component + effect
	ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	ADD_NEW_COMPONENT(URegrowth, Regrowth, DummyActor);

	// Parameters - 1% per second for 5 seconds updating every 0.1 seconds
	constexpr float HotTime = 5;
	constexpr float TickAmount = 1;
	constexpr float TickRate = 0.1f;
	Regrowth->RemainingTime = HotTime;
	Regrowth->Amount = TickAmount;
	Regrowth->Mode = EModificationMode::AddPercentage;
	Regrowth->TickRate = TickRate;

	// Record original
	const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage
	const float Damage = OriginalHP * 0.5f;
	Stats->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Tick the world until regrowth has removed itself
	bool bRegrowthFinished = false;
	uint16 Failsafe=0;
	constexpr float Dt = TickRate/2;
	Regrowth->SetTickGroup(TG_DuringPhysics);
	while (!bRegrowthFinished && Failsafe<10000)
	{

		// We done?
		SEARCH_FOR_COMPONENT(URegrowth, Regrowth, DummyActor);
		bRegrowthFinished = Regrowth == nullptr || !Regrowth->IsRegistered();
		
		// Tick
		if (!bRegrowthFinished)
		{
			Regrowth->TickComponent(Dt, LEVELTICK_All, nullptr);
		}
		
		// Safety first!
		Failsafe++;
		
	}

	// Expected value
	const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const float CurrentHPPlusOne = Stats->GetModifiedValue(EStatEnum::Health, TickAmount, EStatValueType::Current,
		Regrowth->Mode);
	const float SingleTick = CurrentHPPlusOne - CurrentHP;
	const float HealthPerTime = SingleTick/TickRate;
	const float ExpectedHP = OriginalHP - Damage + HealthPerTime * HotTime;
	
	// Test
	const bool Success = FMathf::Abs(CurrentHP - ExpectedHP) < 0.5f;
	if (!Success)
	{
		UE_LOG(LogTemp, Warning, TEXT("Regrowth healing didn't match expected! Current [%s] | Expected [%s]"),
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