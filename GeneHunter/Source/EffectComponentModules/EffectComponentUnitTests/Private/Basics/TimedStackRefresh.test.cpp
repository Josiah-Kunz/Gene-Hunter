/**
 * Tests that the delegates make it to their delegate arrays when an EffectComponent is attached.
 */

#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "Misc/AutomationTest.h"
#include "TimedEffectComponent.h"
#include "TimedStacks_UNITTEST.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_TimedStackRefresh,
                                 "__GeneHunter.Effects.Basics.Timed Stack Refresh",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_TimedStackRefresh::RunTest(const FString& Parameters)
{
	
	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 

	// Attach an effect that will remove itself after a time
	ADD_NEW_COMPONENT(UTimedStacks_UNITTEST, TimedEffect, DummyActor);

	// Safety first!
	uint16 Failsafe = 0;
	constexpr uint16 FailAt = 50000;

	// Time trackers
	float Age = 0;
	float Time = 0;
	constexpr float Dt = 0.1f;
	const float Lifetime = TimedEffect->StartingDuration();
	TimedEffect->SetTickGroup(TG_DuringPhysics);

	// This is just for readability so we know when to tick
	bool bShouldTick = true;

	// Stack stages - we want to add more than the max since it should refresh even if it's at max stacks
	//	- One stack initially
	//	- One stack at Lifetime/2
	//	- Attempted stack at 1.25*Lifetime (should fail, but refreshes duration)
	//		= If it doesn't refresh at Lifetime/2, it'll only last "Lifetime" and the third stack will never happen
	//	- Total time should then be 2.25*Lifetime
	const float StackTime2 = Lifetime/2;
	bool bSecondStack = false;
	const float StackTime3 = 1.25f*Lifetime;
	bool bThirdStack = false;
	const float ExpectedAge = StackTime3 + Lifetime + Dt;	// The +Dt is so it can kill itself

	// Loop longer than the max time
	const float MaxTime = 2*ExpectedAge;
	while (Time < MaxTime && Failsafe < FailAt)
	{

		// Tick?
		bShouldTick = TimedEffect->IsRegistered();
		if (bShouldTick)
		{
			Age += Dt;
			TimedEffect->TickComponent(Dt, LEVELTICK_All, nullptr);
		}

		// Add another stack?
		if (!bSecondStack && Time > StackTime2)
		{
			bSecondStack = true;
			TimedEffect->AddStacks(1);
		} else if (!bThirdStack && Time > StackTime3)
		{
			bThirdStack = true;
			TimedEffect->AddStacks(1);
		}

		// Iterate
		Time += Dt;
		Failsafe++;
	}

	// Did we max out?
	if (Failsafe >= FailAt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Max iterations reached! Maybe TimedEffect isn't ticking?"));
		return false;
	}

	// Test
	const bool bAgeReached = FMathf::Abs(Age - ExpectedAge) < Dt/2;
	if (!bAgeReached)
	{

		if (!bSecondStack)
		{
			UE_LOG(LogTemp, Warning, TEXT("Second stack never happened!"))
		} else if (!bThirdStack)
		{
			UE_LOG(LogTemp, Warning, TEXT("Third stack never happened!"))
		} else
		{
			UE_LOG(LogTemp, Warning, TEXT("Didn't tick for the right amount of time! Actual: [%s] | Expected: [%s]"),
				*FString::SanitizeFloat(Age),
				*FString::SanitizeFloat(ExpectedAge)
				);
		}
		return false;
	}
	
	// Cleanup
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	return true;
}