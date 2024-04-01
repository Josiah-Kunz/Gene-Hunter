#pragma once

#include "ComponentUtilities.h"
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "Priority_Mid_ZeroPoints_UNITTEST.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSilence,
                                 "__GeneHunter.Effects.Basics.Silence",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSilence::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(UAffinitiesComponent, AffinitiesComponent)
	AffinitiesComponent->SetUnspentPoints(3);

	// Cache original to compare
	const uint8 OriginalPoints = AffinitiesComponent->GetUnspentPoints();

	// Attach zero
	ADD_NEW_COMPONENT(UZeroPoints_Mid_UNITTEST, ZeroPointsMid, DummyActor);

	// Test that the points are zero
	uint8 CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should be zero: Original [%i] | Current (zero?) [%i]"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			0,
			0.5f);

	// Silence
	ZeroPointsMid->Silence();

	// Test again
	CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should no longer be zero: Original [%i] | Current (not zero?) [%i]"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			OriginalPoints,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

