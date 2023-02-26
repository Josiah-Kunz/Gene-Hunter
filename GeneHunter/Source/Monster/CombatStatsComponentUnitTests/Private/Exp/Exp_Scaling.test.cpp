#pragma once

#include "CombatStatUnitTestUtilities.h"
#include "ComponentUtilities.h"

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
			StatsComponent->LevelComponent->GetCXP(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test basic setter
	StatsComponent->LevelComponent->SetCXP(10);
	TestEqual(
			"Set to 10",
			StatsComponent->LevelComponent->GetCXP(),
			10,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter over max (1M1)
	StatsComponent->LevelComponent->SetCXP(1000001);
	TestEqual(
			"Set to 1M1 | should cap at 1M",
			StatsComponent->LevelComponent->GetCXP(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter 0
	StatsComponent->LevelComponent->SetCXP(0);
	TestEqual(
			"Set to 0 | should min at 1",
			StatsComponent->LevelComponent->GetCXP(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test setter -1
	StatsComponent->LevelComponent->SetCXP(-1);
	TestEqual(
			"Set to -1 | should min at 1",
			StatsComponent->LevelComponent->GetCXP(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 50
	StatsComponent->LevelComponent->SetLevel(50);
	TestEqual(
			"Level 50",
			StatsComponent->LevelComponent->GetCXP(),
			125000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 100
	StatsComponent->LevelComponent->SetLevel(100);
	TestEqual(
			"Level 100",
			StatsComponent->LevelComponent->GetCXP(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 0
	StatsComponent->LevelComponent->SetLevel(0);
	TestEqual(
			"Level 0",
			StatsComponent->LevelComponent->GetCXP(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level -1
	StatsComponent->LevelComponent->SetLevel(-1);
	TestEqual(
			"Level -1",
			StatsComponent->LevelComponent->GetCXP(),
			1,
			UStatUnitTestUtilities::TOLERANCE);

	// Test level 101
	StatsComponent->LevelComponent->SetLevel(101);
	TestEqual(
			"Level 101",
			StatsComponent->LevelComponent->GetCXP(),
			1000000,
			UStatUnitTestUtilities::TOLERANCE);

	return true;
}