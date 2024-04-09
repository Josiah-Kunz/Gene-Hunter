
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
	const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	const float ExpectedHP = OriginalHP * (1+FullBloom->GetHPIncrease());
	
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
	Stats->ModifyStat(EStatEnum::Health,
		0.5f*FullBloom->GetHPIncrease() * Stats->GetStat(EStatEnum::Health).GetPermanentValue(),
		EStatValueType::Current,
		EModificationMode::SetDirectly);

	// Remove effect and make sure we don't die
	// TODO
	
	const bool bDmgHPSuccess = FMathf::Abs(CurrentHP - ExpectedHP) < 0.1f;
	if (!bFullHPSuccess)
	{
		UE_LOG(LogTemp, Warning, TEXT("FullBloom HP at full health didn't match expected! Current [%s] | Expected [%s]"),
			*FString::SanitizeFloat(CurrentHP),
			*FString::SanitizeFloat(ExpectedHP)
			);
	}

	// Garbage collect
	ComponentUtilities::DestroyDummyWorld(DummyWorld);

	// Return
	return bFullHPSuccess;
}

#pragma endregion