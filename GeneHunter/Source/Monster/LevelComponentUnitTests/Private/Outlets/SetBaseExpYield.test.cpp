#pragma once

#include "UnchangeableBaseYield_UNITTEST.h"
#include "ComponentUtilities.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetBaseExpYield,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.SetBaseExpYield",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSetBaseExpYield::RunTest(const FString& Parameters)
{

	// Set up
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent)

	// Cache original to compare
	const float OriginalYield = LevelComponent->GetBaseExpYield();
	
	// Attach unchangeable
	ADD_NEW_COMPONENT(UUnchangeableBaseYield_UNITTEST, Effect, DummyActor);

	// Try to set new base yield
	constexpr float AttemptedSet = 2.5f;
	LevelComponent->SetBaseExpYield(AttemptedSet);

	// Test if this was set (it shouldn't have been)
	const float CurrentYield = LevelComponent->GetBaseExpYield();
	TestEqual(
			FString::Printf(
			TEXT("Exp yield should be not be changed to %s: Original [%s] | New [%s] (should be the same)"),
				*FString::SanitizeFloat(AttemptedSet),
				*FString::SanitizeFloat(OriginalYield),
				*FString::SanitizeFloat(CurrentYield)
			),
			CurrentYield,
			OriginalYield,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

