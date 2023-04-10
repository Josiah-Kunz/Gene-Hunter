#pragma once

#include "AffinitiesComponent.h"
#include "MoreBaseYield_UNITTEST.h"
#include "ComponentUtilities.h"
#include "TypesUnitTests/Private/TypeUnitTestUtilities.h"
#include "CXPBasedOnType_UNITTEST.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetCXP,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.GetCXP",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetCXP::RunTest(const FString& Parameters)
{

	// Initialize dummy Types
	GET_DUMMY_TYPES()

	// Set up a dummy with a Level
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent);

	// Attach affinities
	ADD_NEW_COMPONENT(UAffinitiesComponent, AffinitiesComponent, DummyActor);

	// Give Affinities a Fire type
	FAffinity FireAffinity = FAffinity{};
	FireAffinity.Type = Fire;
	FireAffinity.SetCurrentPoints(1);
	AffinitiesComponent->Affinities.Add(FireAffinity);

	// Set CXP to 100
	LevelComponent->SetCXP(100);
	const uint32 OriginalCXP = LevelComponent->GetCXP();;
	
	// Attach effect
	ADD_NEW_COMPONENT(UCXPBasedOnType_UNITTEST, Effect, DummyActor);

	// Make sure the effect triggers on Fire
	Effect->TypeToBoost = FireAffinity.Type;

	// Test that the points are increased
	float CurrentCXP = LevelComponent->GetCXP();
	TestEqual(
			FString::Printf(
			TEXT("CXP should be increased by %s: Original [%s] | Increased [%s]"),
				*FString::SanitizeFloat(Effect->BoostFactor),
				*FString::SanitizeFloat(OriginalCXP),
				*FString::SanitizeFloat(CurrentCXP)
			),
			CurrentCXP,
			OriginalCXP * Effect->BoostFactor,
			0.5f);

	// Make sure the effect doesn't trigger on anything else
	Effect->TypeToBoost = Water;

	// Test that the points are increased
	CurrentCXP = LevelComponent->GetCXP();
	TestEqual(
			FString::Printf(
			TEXT("CXP should *not* be increased by %s: Original [%s] | Increased [%s]"),
				*FString::SanitizeFloat(Effect->BoostFactor),
				*FString::SanitizeFloat(OriginalCXP),
				*FString::SanitizeFloat(CurrentCXP)
			),
			CurrentCXP,
			OriginalCXP,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

