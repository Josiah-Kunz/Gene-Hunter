#pragma once

#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "EvenPointsOnly_UNITTEST.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetUnspentPoints,
                                 "__GeneHunter.Effects.Outlets.UAffinitiesComponent.SetUnspentPoints",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSetUnspentPoints::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(UAffinitiesComponent, AffinitiesComponent)
	AffinitiesComponent->SetUnspentPoints(3);

	// Cache original to compare
	const uint8 OriginalPoints = AffinitiesComponent->GetUnspentPoints();
	
	// Attach evenonly
	UEvenPointsOnly_UNITTEST* EvenPoints;
	ADD_COMPONENT(UEvenPointsOnly_UNITTEST, EvenPoints, DummyActor);

	// Try to set points to 2---should work!
	constexpr uint8 SetPointsEven = 2;
	AffinitiesComponent->SetUnspentPoints(SetPointsEven);

	// Test that the points are indeed 2
	uint8 CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("Setting points to 2 should work: Original [%i] | 2 [%i]"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			SetPointsEven,
			0.5f);

	// Try to set points back to 3 (should fail!)
	constexpr uint8 SetPointsOdd = 3;
	AffinitiesComponent->SetUnspentPoints(SetPointsOdd);

	// Test that the points are indeed 2
	CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("Setting points to 3 shouldn't work: Original [%i] | 2 [%i]"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			SetPointsEven,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

