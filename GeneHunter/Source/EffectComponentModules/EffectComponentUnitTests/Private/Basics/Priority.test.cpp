#pragma once

#include "ComponentUtilities.h"		// For ADD_COMPONENT macro
#include "CoreMinimal.h"			// Since we're using ADD_COMPONENT
#include "Priority_Low_DoublePoints_UNITTEST.h"
#include "Priority_Mid_ZeroPoints_UNITTEST.h"
#include "Priority_High_DoublePoints_UNITTEST.h"
#include "Misc/AutomationTest.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FPriority,
                                 "__GeneHunter.Effects.Basics.Priorities",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FPriority::RunTest(const FString& Parameters)
{
	
	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(UAffinitiesComponent, AffinitiesComponent)
	AffinitiesComponent->SetUnspentPoints(3);

	// Cache original to compare
	const uint8 OriginalPoints = AffinitiesComponent->GetUnspentPoints();

	// Attach effects:
	// One should be a double effect
	// Another should be a zero effect
	// Test order!

	// Attach double
	UDoublePoints_Low_UNITTEST* DoublePointsLow;
	ADD_COMPONENT(UDoublePoints_Low_UNITTEST, DoublePointsLow, DummyActor);

	// Attach zero
	UZeroPoints_Mid_UNITTEST* ZeroPointsMid;
	ADD_COMPONENT(UZeroPoints_Mid_UNITTEST, ZeroPointsMid, DummyActor);

	// Test that the points are doubled because priority is higher
	uint8 CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should be zero: Original [%i] | Zero [%i] (if doubled, Priorities are messed up!)"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			0,
			0.5f);

	// Attach high double
	UDoublePoints_High_UNITTEST* DoublePointsHigh;
	ADD_COMPONENT(UDoublePoints_High_UNITTEST, DoublePointsHigh, DummyActor);

	// Test that the points are doubled because priority is higher
	CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should be zero: Original [%i] | Double [%i] (if zero, Priorities are messed up!)"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			2*OriginalPoints,
			0.5f);

	// GC
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	
	return true;
}

