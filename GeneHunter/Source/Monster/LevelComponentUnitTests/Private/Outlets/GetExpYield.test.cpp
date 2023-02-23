#pragma once

#include "MoreYield_UNITTEST.h"
#include "ComponentUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetExpYield,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.GetExpYield",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetExpYield::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent)

	// Cache original to compare (note: testing against self)
	const float OriginalYield = LevelComponent->GetExpYield(LevelComponent);
	
	// Attach double
	UMoreYield_UNITTEST* MoreYieldComponent;;
	ADD_COMPONENT(UMoreYield_UNITTEST, MoreYieldComponent, DummyActor);

	// Test that the points are doubled
	float CurrentYield = LevelComponent->GetExpYield(LevelComponent);
	TestEqual(
			FString::Printf(
			TEXT("Exp yield should be increased by %s: Original [%s] | Increased [%s]"),
				*FString::SanitizeFloat(UMoreYield_UNITTEST::YieldMultiplier),
				*FString::SanitizeFloat(OriginalYield),
				*FString::SanitizeFloat(CurrentYield)
			),
			CurrentYield,
			UMoreYield_UNITTEST::YieldMultiplier*OriginalYield,
			0.5f);

	// GC
	DUMMY_TEST_GC
	
	return true;
}

