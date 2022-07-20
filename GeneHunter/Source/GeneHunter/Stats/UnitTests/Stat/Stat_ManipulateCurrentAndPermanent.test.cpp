#pragma once

#include "GeneHunter/Stats/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_Stat_ManipulateCurrentAndPermanent,
	"UStat.Stat.Manipulate Current & Permanent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_Stat_ManipulateCurrentAndPermanent::RunTest(const FString& Parameters)
{

	// Set up
	UStat* DummyStat = NewObject<UStat>();
	DummyStat->SetCurrentValue(100);
	DummyStat->SetPermanentValue(200);
	
	// Tests
	TestEqual(
			"UStat::SetCurrent(100)",
			DummyStat->GetCurrentValue(),
			100,
			UStatUnitTestUtilities::TOLERANCE);
	TestEqual(
			"UStat::SetPermanent(200)",
			DummyStat->GetPermanentValue(),
			200,
			UStatUnitTestUtilities::TOLERANCE);

	return true;
}