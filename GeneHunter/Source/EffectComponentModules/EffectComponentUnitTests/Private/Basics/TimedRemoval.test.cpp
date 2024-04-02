/**
 * Tests that the delegates make it to their delegate arrays when an EffectComponent is attached.
 */

#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "Misc/AutomationTest.h"
#include "TimedEffectComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_TimedRemoval,
                                 "__GeneHunter.Effects.Basics.Timed Removal",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_TimedRemoval::RunTest(const FString& Parameters)
{
	
	// Initialize world
	UWorld* DummyWorld;
	AActor* DummyActor; 
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); 

	// Attach an effect that will remove itself after a time
	ADD_NEW_COMPONENT(UTimedEffectComponent, TimedEffect, DummyActor);

	// Set the kill timer
	constexpr float Lifetime = 2.5f;
	TimedEffect->RemainingTime = Lifetime;
	TimedEffect->SetTickGroup(TG_DuringPhysics);

	// Safety first!
	uint16 Failsafe = 0;
	constexpr uint16 FailAt = 50000;

	// Loop for longer than the maximum lifetime so we know it's really gone
	float Age = 0;
	float Time = 0;
	constexpr float Dt = 0.1f;
	bool bShouldTick = true;
	constexpr float MaxTime = 2*Lifetime;
	while (Time < MaxTime && Failsafe < FailAt)
	{

		// Tick?
		bShouldTick = TimedEffect->IsRegistered();
		if (bShouldTick)
		{
			Age += Dt;
			TimedEffect->TickComponent(Dt, LEVELTICK_All, nullptr);
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
	//	- Note: Age should be one tick more than Lifetime since on that last tick, the effect removes itself
	//		(and does nothing else).
	const bool bAgeReached = FMathf::Abs(Age - (Lifetime + Dt)) < Dt/2;
	if (!bAgeReached)
	{
		UE_LOG(LogTemp, Warning, TEXT("Age never reached! Age [%s] | Expected lifetime [%s]"),
			*FString::SanitizeFloat(Age),
			*FString::SanitizeFloat(Lifetime)
			);
		return false;
	}
	
	// Cleanup
	ComponentUtilities::DestroyDummyWorld(DummyWorld);
	return true;
}