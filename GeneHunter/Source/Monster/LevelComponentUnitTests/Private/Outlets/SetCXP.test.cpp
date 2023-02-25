#pragma once

#include "CXPLuckyEgg_UNITTEST.h"
#include "ComponentUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FSetCXP,
                                 "__GeneHunter.Effects.Outlets.ULevelComponent.SetCXP",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FSetCXP::RunTest(const FString& Parameters)
{

	// Set up a dummy with a Level
	DUMMY_TEST_COMPONENT(ULevelComponent, LevelComponent);

	// Set CXP to 100
	LevelComponent->SetCXP(100);
	const uint32 OriginalCXP = LevelComponent->GetCXP();
	
	// Attach effect
	ADD_NEW_COMPONENT(UCXPLuckyEgg_UNITTEST, Effect, DummyActor);

	// Set CXP again
	const uint32 AddedCXP = 50;
	LevelComponent->AddExp(AddedCXP);

	// Test that the points are increased
	float CurrentCXP = LevelComponent->GetCXP();
	float ExpectedCXP = OriginalCXP + AddedCXP * Effect->BoostFactor;
	TestEqual(
			FString::Printf(
			TEXT("CXP should be increased by %s: Original [%s] | Should be [%s] | Was [%s]"),
				*FString::SanitizeFloat(Effect->BoostFactor * AddedCXP),
				*FString::SanitizeFloat(OriginalCXP),
				*FString::SanitizeFloat(ExpectedCXP),
				*FString::SanitizeFloat(CurrentCXP)
			),
			CurrentCXP,
			ExpectedCXP,
			0.5f);

	// Double AGAINE!
	ADD_NEW_COMPONENT(UCXPLuckyEgg_UNITTEST, EffectTwo, DummyActor);
	LevelComponent->AddExp(AddedCXP);

	// Test AGAINE!
	CurrentCXP = LevelComponent->GetCXP();
	ExpectedCXP += AddedCXP * Effect->GetStacks() * Effect->BoostFactor;
	TestEqual(
			FString::Printf(
			TEXT("CXP should be increased AGAINE by %s: Original [%s] | Should be [%s] | Was [%s] | Had [%i] stacks."),
				*FString::SanitizeFloat(AddedCXP * Effect->BoostFactor * Effect->GetStacks()),
				*FString::SanitizeFloat(OriginalCXP),
				*FString::SanitizeFloat(ExpectedCXP),
				*FString::SanitizeFloat(CurrentCXP),
				Effect->GetStacks()
			),
			CurrentCXP,
			ExpectedCXP,
			0.5f);
	
	// GC
	DUMMY_TEST_GC
	
	return true;
}

