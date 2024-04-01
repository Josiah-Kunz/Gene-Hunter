#pragma once

#include "ComponentUtilities.h"		// For ADD_COMPONENT macro
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "MinLevel_UNITTEST.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetMinLevel,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.GetMinLevel",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetMinLevel::RunTest(const FString& Parameters)
{

	// Set up 
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent)

	// Cache original to compare 
	const uint16 OriginalMin = LevelComponent->GetMinLevel();
	
	// Attach effect
	ADD_NEW_COMPONENT(UMinLevel_UNITTEST, Effect, DummyActor);

	// Test that the Min has been raised
	const uint16 CurrentMin = LevelComponent->GetMinLevel();
	TestEqual(
			FString::Printf(
			TEXT("Min level should be %i: Original [%i] | New [%i]"),
				UMinLevel_UNITTEST::NewMinLevel,
				OriginalMin,
				CurrentMin
			),
			CurrentMin,
			UMinLevel_UNITTEST::NewMinLevel,
			0.5f);

	// Test you can try to set it lower but it won't go
	LevelComponent->SetLevel(UMinLevel_UNITTEST::NewMinLevel - 1);
	const uint16 CurrentLevel = LevelComponent->GetLevel();
	TestEqual(
			FString::Printf(
			TEXT("Current level should be @ new Min (%i): Original Min [%i] | Current level [%i]"),
				UMinLevel_UNITTEST::NewMinLevel,
				OriginalMin,
				CurrentLevel
			),
			CurrentLevel,
			UMinLevel_UNITTEST::NewMinLevel,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

