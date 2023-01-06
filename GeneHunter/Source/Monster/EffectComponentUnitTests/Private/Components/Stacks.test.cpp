/**
 * Tests that when duplicate EffectComponents are attached, it will increase the stacks instead of actually attaching
 * two.
 */

#pragma once

#include "StatUnitTestUtilities.h"
#include "BerserkerGene.h"
#include "ComponentUtilities.h"
#include "Stacks_Multiple_UNITTEST.h"
#include "Stacks_Single_UNITTEST.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Stacks,
                                 "__GeneHunter.Effects.Component Tests.Stacks",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Stacks::RunTest(const FString& Parameters)
{
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Attach 2x effects (max is 3)
	ADD_NEW_COMPONENT(UStacks_Multiple_UNITTEST, MultiStacker1, DummyActor);
	ADD_NEW_COMPONENT(UStacks_Multiple_UNITTEST, MultiStacker2, DummyActor);

	// Compare stacks
	constexpr int ExpectedStacks = 2;
	TestTrue(FString::Printf(TEXT("EffectComponent number of stacks mismatch: Expected [%s] | Actual [%s]"),
		*FString::FromInt(ExpectedStacks),
		*FString::FromInt(MultiStacker1->GetStacks())),
	ExpectedStacks - MultiStacker1->GetStacks() == 0);

	// Find how many components there are
	int ComponentCount = 0;
	TSet<UActorComponent*> InstancedComponents = DummyActor->GetComponents();
	for(UActorComponent* ActorComponent : InstancedComponents)
	{
		if (dynamic_cast<UStacks_Multiple_UNITTEST*>(ActorComponent))
			ComponentCount++;
	}

	// Compare components
	constexpr int ExpectedComponents = 1;
	TestTrue(FString::Printf(TEXT("EffectComponent number of components mismatch: Expected [%s] | Actual [%s]"),
		*FString::FromInt(ExpectedComponents),
		*FString::FromInt(ComponentCount)),
	ExpectedComponents - ComponentCount == 0);

	// Get a single stacker and try to add more than its max stacks (i.e., >1)
	ADD_NEW_COMPONENT(UStacks_Single_UNITTEST, SingleStacker1, DummyActor)
	ADD_NEW_COMPONENT(UStacks_Single_UNITTEST, SingleStacker2, DummyActor)

	// Compare stacks
	TestTrue(FString::Printf(TEXT("EffectComponent number of stacks mismatch: Expected [%s] | Actual [%s]"),
		*FString::FromInt(1),
		*FString::FromInt(SingleStacker1->GetStacks())),
	1 - SingleStacker1->GetStacks() == 0);
	
	// Return
	BASESTATS_GC
	return true;
}