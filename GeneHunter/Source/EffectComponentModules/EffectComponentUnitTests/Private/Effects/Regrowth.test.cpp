
#pragma once

#include "ComponentUtilities.h"
#include "Editor.h"
#include "Editor/EditorEngine.h"
#include "GameFramework/Actor.h"
#include "Regrowth.h"
#include "Misc/AutomationTest.h"

/// Need to declare first!

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Regrowth,
	"__GeneHunter.Effects.Component Tests.Regrowth",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

#pragma region Latent test

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FEffectComponent_Components_Regrowth_Latent,
	AActor*, DummyActor,
	bool, bInitialized,
	UWorld*, DummyWorld
	);

bool FEffectComponent_Components_Regrowth_Latent::Update()
{

	// Initialize
	if (!bInitialized)
	{
		
		// Set init
		bInitialized = true;
		
		// Add a stats component + effect
		ADD_NEW_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
		ADD_NEW_COMPONENT(URegrowth, Regrowth, DummyActor);
		ADD_NEW_COMPONENT(UHoTComponent, HoTComponent, DummyActor);

		// Record original
		const float OriginalHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();

		// Take damage
		const float Damage = OriginalHP * 0.5f;
		Stats->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);
		
	}

	// Tick the world
	//DummyActor->GetWorld()->Tick(LEVELTICK_TimeOnly, FApp::GetDeltaTime());
	DummyWorld->Tick(LEVELTICK_TimeOnly, 0.1f);

	// Wait for effect to be done
	URegrowth* Regrowth = nullptr;
	SEARCH_FOR_COMPONENT(URegrowth, Regrowth, DummyActor);
	if ( Regrowth == nullptr || true)
	{
		UE_LOG(LogTemp, Warning, TEXT("Regrowth is nullptr"));
		/*
		// Get values
		const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
		const float PermHP = Stats->GetStat(EStatEnum::Health).GetPermanentValue();
		const float ExpectedHP = PermHP * 0.55f; // The original 50% + 1% for 5 seconds

		// Test
		const bool Success = FMathf::Abs(CurrentHP - ExpectedHP) < 0.5f;
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Regrowth healing didn't match expected! Current [%s] | Expected [%s] | Permanent [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP),
				*FString::SanitizeFloat(PermHP)
				);
		}
		*/

		// Garbage collect
		DummyActor->GetWorld()->DestroyWorld(false);

		// Done either way
		return true;
	}

	UCombatStatsComponent* Stats = nullptr;
	SEARCH_FOR_COMPONENT(UCombatStatsComponent, Stats, DummyActor);
	const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
	/*
	UE_LOG(LogTemp, Warning, TEXT("Regrowth is *NOT* nullptr: [%s] | [%s]"),
		*FString::SanitizeFloat(CurrentHP),
		*(Stats->GetName())
		);
	*/

	// Not done yet
	return false;

	// See if successful
	/*
	const float CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	const float PermHP = StatsComponent->GetStat(EStatEnum::Health).GetPermanentValue();
	const float ExpectedHP = PermHP * 0.55f; // The original 50% + 1% for 5 seconds
	TestTrue(FString::Printf(TEXT("Regrowth healing didn't match expected! Current [%s] | Expected [%s] | Permanent [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP),
				*FString::SanitizeFloat(PermHP)
				), Success);
				*/
}

#pragma endregion

#pragma region Main test

bool UEffectComponent_Components_Regrowth::RunTest(const FString& Parameters)
{

	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 
	//GEditor->GetEditorWorldContext().SetCurrentWorld(DummyWorld);
	
	// Run latent test
	bool bInitialized = false;
	ADD_LATENT_AUTOMATION_COMMAND(FEffectComponent_Components_Regrowth_Latent(DummyActor, bInitialized, DummyWorld)); 
	
	// Just wait for latent tests
	return true;
}

#pragma endregion