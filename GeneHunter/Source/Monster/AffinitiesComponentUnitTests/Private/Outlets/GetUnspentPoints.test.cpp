#pragma once

#include "DoublePoints_UNITTEST.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetUnspentPoints,
                                 "__GeneHunter.Affinities Component.Outlets.GetUnspentPoints",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetUnspentPoints::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_TEST_COMPONENT(UAffinitiesComponent, AffinitiesComponent)
	AffinitiesComponent->SetUnspentPoints(3);

	// Cache original to compare
	const uint8 OriginalPoints = AffinitiesComponent->GetUnspentPoints();
	
	// Attach double
	UDoublePoints_UNITTEST* DoublePoints;
	ADD_COMPONENT(UDoublePoints_UNITTEST, DoublePoints, DummyActor);

	// Test that the points are doubled
	uint8 CurrentPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should be doubled: Original [%i] | Doubled [%i]"),
				OriginalPoints, CurrentPoints
			),
			CurrentPoints,
			2*OriginalPoints,
			0.5f);

	// GC
	DUMMY_TEST_GC
	
	return true;
}

