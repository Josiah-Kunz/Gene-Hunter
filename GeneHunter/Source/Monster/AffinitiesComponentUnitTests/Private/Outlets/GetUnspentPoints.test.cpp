#pragma once

#include "AffinitiesUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FGetUnspentPoints,
	"__GeneHunter.Affinities Component.Outlets.GetUnspentPoints",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FGetUnspentPoints::RunTest(const FString& Parameters)
{

	// Set up and give 3 unspent points
	DUMMY_AFFINITIESCOMPONENT
	AffinitiesComponent->SetUnspentPoints(3);

	// Cache original to compare
	const uint8 OriginalPoints = AffinitiesComponent->GetUnspentPoints();

	// Attach effects TODO:
	// One should be a double effect
	// Another should be a zero effect
	// Test order!

	// Define delegate
	FBeforeGetUnspentPointsDelegate DoublePointsDelegate;
	//DoublePointsDelegate.Delegate.BindDynamic()
	

	// Test that the points are doubled
	const uint8 DoubledPoints = AffinitiesComponent->GetUnspentPoints();
	TestEqual(
			FString::Printf(
			TEXT("UnspentPoints should be doubled: Original [%i] | Doubled [%i] (if zero, Priorities are messed up!)"),
				OriginalPoints, DoubledPoints
			),
			2*OriginalPoints,
			DoubledPoints,
			UAffinitiesUnitTestUtilities::TOLERANCE);

	// GC
	DUMMY_GC
	
	return true;
}

