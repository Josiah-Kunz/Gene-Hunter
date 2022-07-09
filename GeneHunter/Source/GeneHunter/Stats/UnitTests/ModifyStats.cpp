#pragma once

#include "GeneHunter/Stats/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_ModifyStat,
	"UStat.ModifyStat",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_ModifyStat::RunTest(const FString& Parameters)
{
	
	// Set up
	UStat* DummyStat = NewObject<UStat>();

#define DO_TEST(Value, Mode, GainText, Expected) \
	DummyStat->SetCurrentValue(100); \
	DummyStat->ModifyValue(Value, EStatGainType::Current, Mode); \
	const FString GainFString = GainText; \
	TestEqual( \
			"UStat::ModifyValue " + GainFString, \
			DummyStat->GetCurrentValue(), \
			Expected, \
			UStatUnitTestUtilities::TOLERANCE);

	DO_TEST(1.5f, EModificationMode::AddAbsolute, "AddAbsolute (Gain)", 102)
		
	
	/*
	// Absolute gain
	DummyStat.SetCurrentValue(100);
	DummyStat.ModifyValue(1.5f, EStatGainType::Current, EModificationMode::AddAbsolute);
	TestEqual(
			"UStat::ModifyValue (AddAbsolute Gain)",
			DummyStat.GetCurrentValue(),
			101.5f,
			UStatUnitTestUtilities::TOLERANCE);
	
	// Absolute gain
	DummyStat.SetCurrentValue(100);
	DummyStat.ModifyValue(1.5f, EStatGainType::Current, EModificationMode::AddAbsolute);
	TestEqual(
			"UStat::ModifyValue (AddAbsolute Gain)",
			DummyStat.GetCurrentValue(),
			101.5f,
			UStatUnitTestUtilities::TOLERANCE);
			*/
	
	// Return
	return true;
}