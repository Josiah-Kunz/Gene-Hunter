#pragma once

#include "CombatStatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_Stat_ManipulateCurrentAndPermanent,
	"__GeneHunter.FStat.Stat.Manipulate Current & Permanent",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_Stat_ManipulateCurrentAndPermanent::RunTest(const FString& Parameters)
{

	// Set up
	FCombatStat DummyStat = {};
	DummyStat.SetCurrentValue(100);
	DummyStat.SetPermanentValue(200);
	
	// Tests
	TestEqual(
			"FCombatStat::SetCurrent(100)",
			DummyStat.GetCurrentValue(),
			100,
			UStatUnitTestUtilities::TOLERANCE);
	TestEqual(
			"FCombatStat::SetPermanent(200)",
			DummyStat.GetPermanentValue(),
			200,
			UStatUnitTestUtilities::TOLERANCE);

	return true;
}