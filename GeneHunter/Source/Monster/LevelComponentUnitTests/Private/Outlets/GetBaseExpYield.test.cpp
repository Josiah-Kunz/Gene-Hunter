#pragma once

#include "MoreBaseYield_UNITTEST.h"
#include "ComponentUtilities.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetBaseExpYield,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.GetBaseExpYield",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetBaseExpYield::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent)

	// Cache original to compare
	const float OriginalYield = LevelComponent->GetBaseExpYield();
	
	// Attach double
	UMoreBaseYield_UNITTEST* MoreYieldComponent;;
	ADD_COMPONENT(UMoreBaseYield_UNITTEST, MoreYieldComponent, DummyActor);

	// Test that the points are doubled
	float CurrentYield = LevelComponent->GetBaseExpYield();
	TestEqual(
			FString::Printf(
			TEXT("Exp yield should be increased by %s: Original [%s] | Increased [%s]"),
				*FString::SanitizeFloat(UMoreBaseYield_UNITTEST::YieldMultiplier),
				*FString::SanitizeFloat(OriginalYield),
				*FString::SanitizeFloat(CurrentYield)
			),
			CurrentYield,
			UMoreBaseYield_UNITTEST::YieldMultiplier*OriginalYield,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

