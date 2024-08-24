#pragma once

#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "CombatStatsComponent.h"
#include "CombatStatUnitTestUtilities.h"
#include "MoveData.h"
#include "Misc/AutomationTest.h"
#include "Type.h"
#include "TypesUnitTests/Private/TypeUnitTestUtilities.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_DamageFormula,
	"__GeneHunter.Combat.Damage formula",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

/**
 * Tests moves from a Flying/Grass attacker to a Fighting/Fire defender with 120 base stats across the board:
 *	 [Lv. 1]	10 base power Fighting with 0% chance to crit
 *	 [Lv. 50]	50 base power Flying with 100% chance to crit
 *	 [Lv. 100]	100 base power Electric with 130% chance to crit
 */
bool FUStat_DamageFormula::RunTest(const FString& Parameters)
{

	// Get static data
	GET_DUMMY_MOVEDATA()
	GET_DUMMY_TYPES()


	// "DummyActor" is the attacker
	// ----------------------------
	
	// Attacking stats
	DUMMY_BASE_STATS_BLOCK
	BaseStats = { 100, 100, 100, 100, 100, 100, 100}; \
	StatsComponent->ModifyStats(BaseStats, EStatValueType::BaseStat, EModificationMode::SetDirectly);
	StatsComponent->ModifyStatsUniformly(100, EStatValueType::BasePairs, EModificationMode::SetDirectly);
	StatsComponent->RecalculateStats(true);
	
	// Attacking affinities
	ADD_NEW_COMPONENT(UAffinitiesComponent, AttackingAffinities, DummyActor);
	FAffinity FlyingAffinity = {};
	FlyingAffinity.Type = Flying;
	FlyingAffinity.SetCurrentPoints(1);
	FAffinity GrassAffinity = {};
	GrassAffinity.Type = Grass;
	GrassAffinity.SetCurrentPoints(2);
	AttackingAffinities->Affinities = {FlyingAffinity, GrassAffinity};

	// Now the defender
	// ----------------

	// Creation
	AActor* DefenderActor;
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DefenderActor);

	// Defending stats
	ADD_NEW_COMPONENT(UCombatStatsComponent, DefendingStats, DefenderActor);
	DefendingStats->ModifyStatsUniformly(100, EStatValueType::BaseStat, EModificationMode::SetDirectly);
	DefendingStats->ModifyStatsUniformly(100, EStatValueType::BasePairs, EModificationMode::SetDirectly);
	DefendingStats->RecalculateStats(true);

	// Defending affinities
	ADD_NEW_COMPONENT(UAffinitiesComponent, DefendingAffinities, DefenderActor);
	FAffinity FightingAffinity = {};
	FightingAffinity.Type = Fighting;
	FightingAffinity.SetCurrentPoints(1);
	FAffinity FireAffinity = {};
	FireAffinity.Type = Fire;
	FireAffinity.SetCurrentPoints(2);
	DefendingAffinities->Affinities = {FightingAffinity, FireAffinity};

	// Set up conditions
	const TArray<float> CritValues = {0, 100, 130};
	const TArray<int32> Levels = {1, 50, 100};
	const TArray<UMoveData*> MoveDatas = {Fighting10, Flying50, Electric100};
	const TArray<float> ExpectedValues = {2.48f, 26244.0f, 9140785.2f};

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
		StatsComponent->LevelComponent->SetLevel(Level);
		DefendingStats->LevelComponent->SetLevel(Level);

		// Set crit
		StatsComponent->ModifyStat(EStatEnum::CriticalHit, CritValue, EStatValueType::Current,
			EModificationMode::SetDirectly);

		// Calculate damage
		const float Damage = DefendingStats->CalculateDamage(MoveData, StatsComponent);

		// Compare
		bSuccess &= TestEqual(
			FString::Printf(TEXT("Move [%s] with [%s] Base Power"),
				*MoveData->GetName(),
				*FString::SanitizeFloat(MoveData->BasePower)
			),
			Damage, ExpectedValue, 1e-3f);
		
	}
	
	// Destroy the world
	BASESTATS_GC

	return bSuccess;
	
}