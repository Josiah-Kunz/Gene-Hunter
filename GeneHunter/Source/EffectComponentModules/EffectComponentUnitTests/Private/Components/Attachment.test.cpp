/**
 * Tests that the delegates make it to their delegate arrays when an EffectComponent is attached.
 */

#pragma once

#include "ComponentUtilities.h"
#include "MathUtil.h"
#include "StatUnitTestUtilities.h"
#include "BerserkerGene.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Attachment,
	"__GeneHunter.Effects.Component Tests.Attachment",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Attachment::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Attach an effect
	UBerserkerGene* BerserkerGene = nullptr;
	REQUIRE_COMPONENT(UBerserkerGene, BerserkerGene, DummyActor)

	// Test that it auto recognized StatsComponent
	TestTrue(FString::Printf(TEXT("EffectComponent found StatsComponent automatically?")),
	BerserkerGene->StatsComponent != nullptr);
	
	// Return
	BASESTATS_GC
	return true;
}