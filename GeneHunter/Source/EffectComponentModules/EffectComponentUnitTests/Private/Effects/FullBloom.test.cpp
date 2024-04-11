
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
	"__GeneHunter.Effects.Component Tests.Full Bloom",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Main test

bool UEffectComponent_Components_FullBloom::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 

	// Add a stats component and record OG HP
	ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();

	// +20% (hopefully)
	ADD_NEW_COMPONENT(UFullBloom, FullBloom, DummyActor);

	// Expected value
	float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	float ExpectedHP = OriginalHP * (1+FullBloom->GetHPIncrease()/100);
	
	// Test
	const bool bFullHPSuccess = FMathf::Abs(CurrentHP - ExpectedHP) < 0.1f;
	if (!bFullHPSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("FullBloom HP at full health didn't match expected! Current [%s] | Expected [%s]"),
			*FString::SanitizeFloat(CurrentHP),
			*FString::SanitizeFloat(ExpectedHP)
			);
	}

	// Go to 10% health
	const float DamagedHP = 0.5f*FullBloom->GetHPIncrease()/100 * Stats->GetStat(EStatEnum::Health).GetPermanentValue(); 
	Stats->ModifyStat(EStatEnum::Health,
		DamagedHP,
		EStatValueType::Current,
		EModificationMode::SetDirectly);

	// Remove effect and make sure we don't die
	//FullBloom->DestroyComponent();
	FullBloom->UnregisterComponent();

	// Get new expected HP
	const float NewPermHP = OriginalHP * (1+FullBloom->GetHPIncrease()/100);
	ExpectedHP = OriginalHP/NewPermHP * DamagedHP;
	
	// Test
	CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const bool bRmvSuccess = FMathf::Abs(CurrentHP - ExpectedHP) < 0.1f;
	if (!bRmvSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("Removed FullBloom and the HP didn't scale correctly! Current [%s] | Expected [%s]"),
			*FString::SanitizeFloat(CurrentHP),
			*FString::SanitizeFloat(ExpectedHP)
			);
	}

	// Garbage collect
	ComponentUtilities::DestroyDummyWorld(DummyWorld);

	// Return
	return bFullHPSuccess && bRmvSuccess;
}

#pragma endregion