#pragma once

#include "ComponentUtilities.h"
#include "MaxLevel_UNITTEST.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetMaxLevel,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.GetMaxLevel",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetMaxLevel::RunTest(const FString& Parameters)
{

	// Set up 
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent)

	// Cache original to compare 
	const uint16 OriginalMax = LevelComponent->GetMaxLevel();
	
	// Attach effect
	ADD_NEW_COMPONENT(UMaxLevel_UNITTEST, Effect, DummyActor);

	// Test that the max has been raised
	const uint16 CurrentMax = LevelComponent->GetMaxLevel();
	TestEqual(
			FString::Printf(
			TEXT("Max level should be %i: Original [%i] | New [%i]"),
				UMaxLevel_UNITTEST::NewMaxLevel,
				OriginalMax,
				CurrentMax
			),
			CurrentMax,
			UMaxLevel_UNITTEST::NewMaxLevel,
			0.5f);

	// Test you can actually set it that high
	LevelComponent->SetLevel(UMaxLevel_UNITTEST::NewMaxLevel);
	const uint16 CurrentLevel = LevelComponent->GetLevel();
	TestEqual(
			FString::Printf(
			TEXT("Current level should be @ new max (%i): Original max [%i] | Current level [%i]"),
				UMaxLevel_UNITTEST::NewMaxLevel,
				OriginalMax,
				CurrentLevel
			),
			CurrentLevel,
			UMaxLevel_UNITTEST::NewMaxLevel,
			0.5f);

	// GC
	DUMMY_TEST_GC
	
	return true;
}

