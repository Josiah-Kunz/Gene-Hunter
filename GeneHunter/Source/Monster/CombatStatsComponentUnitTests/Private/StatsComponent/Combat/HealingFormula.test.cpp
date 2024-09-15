#pragma once

#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "CombatStatsComponent.h"
#include "CombatStatUnitTestUtilities.h"
#include "MoveData.h"
#include "Misc/AutomationTest.h"
#include "Type.h"
#include "TypesUnitTests/Private/TypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_HealingFormula,
	"__GeneHunter.Combat.Healing formula",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests moves from a Flying/Grass attacker to a Fighting/Fire defender with 120 base stats across the board:
 *	 [Lv. 1]	10 base power Fire with 0% chance to crit
 *	 [Lv. 50]	50 base power Grass (STAB) with 100% chance to crit
 *	 [Lv. 100]	50 base power Ice with 130% chance to crit
 */
bool FUStat_HealingFormula::RunTest(const FString& Parameters)
{
	// Create attacker + defender
	DUMMY_COMBATANTS()

	// Set up conditions
	const TArray<float> CritValues = {0, 100, 130};
	const TArray<int32> Levels = {1, 50, 100};
	const TArray<UMoveData*> MoveDatas = {FireHeal10, GrassHoT50, IceHeal100};
	const TArray<float> ExpectedValues = {-2.48f, -13122.0f, -4676680.8f};

	// Execute tests
	bool bSuccess = true;
	for(uint8 i=0; i<Levels.Num(); i++)
	{

		// Get iterative data
		const float CritValue = CritValues[i];
		const int32 Level = Levels[i];
		const UMoveData* MoveData = MoveDatas[i];
		const float ExpectedValue = ExpectedValues[i];
		
		// Set levels equal
		AtkStats->LevelComponent->SetLevel(Level);
		DefStats->LevelComponent->SetLevel(Level);

		// Set crit
		AtkStats->ModifyStat(EStatEnum::CriticalHit, CritValue, EStatValueType::Current,
			EModificationMode::SetDirectly);

		// Calculate damage
		const float Damage = DefStats->CalculateDamage(MoveData, AtkStats);

		// Compare
		bSuccess &= TestEqual(
			FString::Printf(TEXT("Move [%s] with [%s] Base Power"),
				*MoveData->GetName(),
				*FString::SanitizeFloat(MoveData->BasePower)
			),
			Damage, ExpectedValue, FMathf::Abs(ExpectedValue*1e-6f));
		
	}
	
	// Destroy the world
	BASESTATS_GC

	return bSuccess;
	
}