
#pragma once

#include "ComponentUtilities.h"
#include "CombatStatUnitTestUtilities.h"
#include "MathUtil.h"
#include "Regrowth.h"
#include "Tests/AutomationCommon.h"

#pragma region Latent test

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FEffectComponent_Components_Regrowth_Latent,
	UCombatStatsComponent*, Stats,
	bool&, Success,
	float&, Time
	);

bool FEffectComponent_Components_Regrowth_Latent::Update()
{
	UE_LOG(LogTemp, Warning, TEXT("Time: [%s]"),
		*FString::SanitizeFloat(Stats->GetWorld()->GetTimeSeconds() - Time)
		);
	// Wait for effect to be done
	URegrowth* Regrowth = nullptr;
	SEARCH_FOR_COMPONENT(URegrowth, Regrowth, Stats->GetOwner());
	
	if ( Stats->GetWorld()->GetTimeSeconds() - Time >= 5 )
	{
		// Get values
		const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
		const float PermHP = Stats->GetStat(EStatEnum::Health).GetPermanentValue();
		const float ExpectedHP = PermHP * 0.55f; // The original 50% + 1% for 5 seconds

		// Test
		Success = FMathf::Abs(CurrentHP - ExpectedHP) < 0.5f;
		if (!Success)
		{
			UE_LOG(LogTemp, Warning, TEXT("Regrowth healing didn't match expected! Current [%s] | Expected [%s] | Permanent [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP),
				*FString::SanitizeFloat(PermHP)
				);
		}

		// Done either way
		return true;
	} else
	{
		const float CurrentHP = Stats->GetStat(EStatEnum::Health).GetCurrentValue();
		UE_LOG(LogTemp, Warning, TEXT("Health [%s]"),
				*FString::SanitizeFloat(CurrentHP))
	}

	// Not done yet
	return false;
}

#pragma endregion

#pragma region Main test

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Regrowth,
	"__GeneHunter.Effects.Component Tests.Regrowth",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Regrowth::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Record original
	const float OriginalHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();

	// Take damage
	const float Damage = OriginalHP * 0.5f;
	StatsComponent->ModifyStat(EStatEnum::Health, -Damage, EStatValueType::Current, EModificationMode::AddAbsolute);

	// Add effect
	ADD_NEW_COMPONENT(URegrowth, Regrowth, StatsComponent->GetOwner());
	
	// Run test
	bool Success;
	float Time = StatsComponent->GetWorld()->GetTimeSeconds();
	ADD_LATENT_AUTOMATION_COMMAND(FEngineWaitLatentCommand(2.0f));
	ADD_LATENT_AUTOMATION_COMMAND(FEffectComponent_Components_Regrowth_Latent(StatsComponent, Success, Time));

	// See if successful
	const float CurrentHP = StatsComponent->GetStat(EStatEnum::Health).GetCurrentValue();
	const float PermHP = StatsComponent->GetStat(EStatEnum::Health).GetPermanentValue();
	const float ExpectedHP = PermHP * 0.55f; // The original 50% + 1% for 5 seconds
	TestTrue(FString::Printf(TEXT("Regrowth healing didn't match expected! Current [%s] | Expected [%s] | Permanent [%s]"),
				*FString::SanitizeFloat(CurrentHP),
				*FString::SanitizeFloat(ExpectedHP),
				*FString::SanitizeFloat(PermHP)
				), Success);
	
	// Just wait for latent tests
	return true;
}

#pragma endregion