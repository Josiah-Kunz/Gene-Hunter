/**
 * Tests that the delegates make it to their delegate arrays when an EffectComponent is attached.
 */

#pragma once

#include "BerserkerGene.h"
#include "CombatStatUnitTestUtilities.h"
#include "ComponentUtilities.h"
#include "Misc/AutomationTest.h"
#include "PermStatMod.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(UEffectComponent_Components_Attachment,
	"__GeneHunter.Effects.Basics.Attachment",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool UEffectComponent_Components_Attachment::RunTest(const FString& Parameters)
{
	
	// Get dummy
	DUMMY_BASE_STATS_BLOCK

	// Attach BerserkerGene, which also attaches PermStatMod
	ADD_NEW_COMPONENT(UBerserkerGene, BerserkerGene, DummyActor)
	const UPermStatMod* PermStatMod = DummyActor->FindComponentByClass<UPermStatMod>();
	
	//UPermStatMod* PermStatMod = nullptr;
	//REQUIRE_COMPONENT(UPermStatMod, PermStatMod, DummyActor)

	// Test that it auto recognized StatsComponent
	TestTrue(FString::Printf(TEXT("PermStatMod was added automatically?")),
	PermStatMod->StatsComponent != nullptr);
	
	// Return
	BASESTATS_GC
	return true;
}