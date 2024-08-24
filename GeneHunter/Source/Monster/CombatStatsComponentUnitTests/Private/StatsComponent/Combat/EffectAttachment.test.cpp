#pragma once

#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "CombatStatsComponent.h"
#include "CombatStatUnitTestUtilities.h"
#include "MoveData.h"
#include "Regrowth.h"
#include "Misc/AutomationTest.h"
#include "Type.h"
#include "TypesUnitTests/Private/TypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_EffectAttachment,
	"__GeneHunter.Combat.Effect attachment + stacks",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests that a MoveData attaches an Effect with the correct number of stacks.
 *
 * Details:
 * a Move (50 base power Grass (STAB) with 0% chance to crit) from a Flying/Grass attacker to a Fighting/Fire
 * defender with 120 base stats across the board.
 */
bool FUStat_EffectAttachment::RunTest(const FString& Parameters)
{
	// Create attacker + defender
	DUMMY_COMBATANTS()

	// Settings
	const uint8 ExpectedNumStacks = 3;
	const float CritValue = 0;
	const int32 Level = 50;
	UMoveData* MoveData = GrassHoT50;

	// Set levels equal
	AtkStats->LevelComponent->SetLevel(Level);
	DefStats->LevelComponent->SetLevel(Level);

	// Set crit
	AtkStats->ModifyStat(EStatEnum::CriticalHit, CritValue, EStatValueType::Current,
		EModificationMode::SetDirectly);
	
	// Apply
	DefStats->ApplyMoveData(MoveData, AtkStats);

	// Check attachment
	URegrowth* Regrowth = nullptr;
	SEARCH_FOR_COMPONENT(URegrowth, Regrowth, DefActor);
	const bool bAttached = Regrowth != nullptr;
	if (!bAttached)
	{
		UE_LOG(LogTemp, Warning, TEXT("Regrowth Effect never attached! Cannot evaluate number of stacks."))
		return false;
	}

	// Check number of stacks
	const uint8 NumStacks = Regrowth->GetStacks();
	const bool bStacksCorrect = TestEqual(
			FString::Printf(TEXT("Number of stacks")),
			NumStacks, ExpectedNumStacks, 0.5f);
	
	// Destroy the world
	BASESTATS_GC

	return bStacksCorrect;
	
}