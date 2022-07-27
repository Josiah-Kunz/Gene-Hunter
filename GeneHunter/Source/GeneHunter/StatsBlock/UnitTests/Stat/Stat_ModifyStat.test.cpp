#pragma once

#include "GeneHunter/StatsBlock/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_Stat_ModifyStat,
	"FStat.Stat.ModifyStat",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_Stat_ModifyStat::RunTest(const FString& Parameters)
{
	
	// Set up
	FStat* DummyStat = {};
	FString GainFString;

	// Do tests (afaik, can't make ths a function because we only have access to the .cpp file)
#define DO_TEST(InitialValue, Modifier, Mode, GainText, Expected) \
	DummyStat->SetCurrentValue(InitialValue); \
	DummyStat->ModifyValue(Modifier, EStatValueType::Current, Mode); \
	GainFString = GainText; \
	TestEqual( \
			"FStat::GetModification " + GainFString, \
			DummyStat->GetCurrentValue(), \
			Expected, \
			UStatUnitTestUtilities::TOLERANCE);

	DO_TEST(100, 1.5f, EModificationMode::AddAbsolute, "AddAbsolute 1", 101.5f)
	DO_TEST(100, -10.5, EModificationMode::AddAbsolute, "AddAbsolute 2", 89.5f)
	DO_TEST(100, 1.5f, EModificationMode::AddFraction, "AddFraction 1", 250)
	DO_TEST(100, 0.5f, EModificationMode::AddFraction, "AddFraction 2", 150)
	DO_TEST(200, 1.5f, EModificationMode::AddPercentage, "AddPercentage 1", 203)
	DO_TEST(30, 50, EModificationMode::AddPercentage, "AddPercentage 2", 45)
	DO_TEST(100, 1.5f, EModificationMode::MultiplyAbsolute, "MultiplyAbsolute 1", 150)
	DO_TEST(100, 0.5f, EModificationMode::MultiplyAbsolute, "MultiplyAbsolute 2", 50)
	DO_TEST(200, 1.5f, EModificationMode::MultiplyPercentage, "MultiplyPercentage 1", 3)
	DO_TEST(30, 50, EModificationMode::MultiplyPercentage, "MultiplyPercentage 2", 15)
	DO_TEST(100, -10, EModificationMode::MultiplyAbsolute, "Stats can't be negative", 100)
	
	// Return
	return true;
}