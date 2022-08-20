#pragma once

#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FExp_Scaling,
	"__GeneHunter.Exp.Scaling",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FExp_Scaling::RunTest(const FString& Parameters)
{

	// Set up
	DUMMY_BASE_STATS_BLOCK
	
	// Test level 1
	TestEqual(
			"1 exp to start",
			StatsComponent->GetCumulativeExp(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test basic setter
	StatsComponent->SetCumulativeExp(10);
	TestEqual(
			"Set to 10",
			StatsComponent->GetCumulativeExp(),
			10,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter over max (1M1)
	StatsComponent->SetCumulativeExp(1000001);
	TestEqual(
			"Set to 1M1 | should cap at 1M",
			StatsComponent->GetCumulativeExp(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter 0
	StatsComponent->SetCumulativeExp(0);
	TestEqual(
			"Set to 0 | should min at 1",
			StatsComponent->GetCumulativeExp(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter -1
	StatsComponent->SetCumulativeExp(-1);
	TestEqual(
			"Set to -1 | should min at 1",
			StatsComponent->GetCumulativeExp(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 50
	StatsComponent->SetLevel(50);
	TestEqual(
			"Level 50",
			StatsComponent->GetCumulativeExp(),
			125000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 100
	StatsComponent->SetLevel(100);
	TestEqual(
			"Level 100",
			StatsComponent->GetCumulativeExp(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 0
	StatsComponent->SetLevel(0);
	TestEqual(
			"Level 0",
			StatsComponent->GetCumulativeExp(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level -1
	StatsComponent->SetLevel(-1);
	TestEqual(
			"Level -1",
			StatsComponent->GetCumulativeExp(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 101
	StatsComponent->SetLevel(101);
	TestEqual(
			"Level 101",
			StatsComponent->GetCumulativeExp(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	return true;
}