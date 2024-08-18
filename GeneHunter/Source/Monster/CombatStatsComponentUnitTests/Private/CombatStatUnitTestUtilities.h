#pragma once
#include "CombatStatsComponent.h"
#include "CombatStatUnitTestUtilities.generated.h"

UCLASS()
class UStatUnitTestUtilities : public UBlueprintFunctionLibrary
{
public:

	GENERATED_BODY()
	
	constexpr static float TOLERANCE = 0.1F;

#define DUMMY_BASE_STATS_BLOCK \
	DUMMY_TEST_COMPONENT(UCombatStatsComponent, StatsComponent) \
	StatsComponent->EnsureLevelComponent(DummyActor); \
	StatsComponent->LevelComponent->SetLevel(1); \
	TArray<float> BaseStats = { 116, 100, 100, 60, 90, 50, 120}; \
	StatsComponent->ModifyStats(BaseStats, EStatValueType::BaseStat, EModificationMode::SetDirectly); \
	StatsComponent->RecalculateStats(true);

#define BASESTATS_GC \
	DummyWorld->DestroyWorld(false);

/**
 * A macro to get "dummy" MoveData. These are special, independent of
 *	in-game data (and hence are good for unit tests).
 */
#define GET_DUMMY_MOVEDATA() \
	TArray<UMoveData*> AllDummyMoveData; \
	UMoveData::GetAllMoveData(AllDummyMoveData, {}, true, true);  \
	/* Damage */ \
	UMoveData* Fighting10	= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-Fighting10"))); \
	UMoveData* Flying50		= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-Flying50"))); \
	UMoveData* Electric100	= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-Electric100"))); \
	/* Heal */ \
	UMoveData* FireHeal10	= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-FireHeal10"))); \
	UMoveData* GrassHoT50	= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-GrassHoT50"))); \
	UMoveData* IceHeal100	= UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-IceHeal100"))); \
	/* Status */ \
	UMoveData* TypelessBrokenSoul = UMoveData::GetMoveDataByName(AllDummyMoveData, FName(TEXT("Dummy-TypelessBrokenSoul"))); \

/**
 * Creates:
 *	- DummyWorld
 *	- AtkActor
 *	- AtkStats
 *		= Base stats uniformly set to 100
 *		= Base pairs uniformly set to 100
 *	- AtkAffinities (Flying/Grass)
 *	- Same for Defender except Fighting/Fire
 */
#define DUMMY_COMBATANTS() \
	/* Get static data */ \
	GET_DUMMY_MOVEDATA() \
	GET_DUMMY_TYPES() \
	UWorld* DummyWorld; \
	DummyWorld = NUTNet::CreateUnitTestWorld(true); \
	\
	/* Attacker */ \
	/* -------- */ \
	\
	/* Attacking stats */ \
	AActor* AtkActor = DummyWorld->SpawnActor(AActor::StaticClass()); \
	ADD_NEW_COMPONENT(UCombatStatsComponent, AtkStats, AtkActor); \
	AtkStats->ModifyStatsUniformly(100, EStatValueType::BaseStat, EModificationMode::SetDirectly); \
	AtkStats->ModifyStatsUniformly(100, EStatValueType::BasePairs, EModificationMode::SetDirectly); \
	AtkStats->RecalculateStats(true); \
	\
	/* Attacking affinities */ \
	ADD_NEW_COMPONENT(UAffinitiesComponent, AtkAffinities, AtkActor); \
	FAffinity FlyingAffinity = {}; \
	FlyingAffinity.Type = Flying; \
	FlyingAffinity.SetCurrentPoints(1); \
	FAffinity GrassAffinity = {}; \
	GrassAffinity.Type = Grass; \
	GrassAffinity.SetCurrentPoints(2); \
	AtkAffinities->Affinities = {FlyingAffinity, GrassAffinity}; \
	\
	/* Defender */ \
	/* -------- */ \
	\
	/* Defending stats */ \
	AActor* DefActor = DummyWorld->SpawnActor(AActor::StaticClass()); \
	ADD_NEW_COMPONENT(UCombatStatsComponent, DefStats, DefActor); \
	DefStats->ModifyStatsUniformly(100, EStatValueType::BaseStat, EModificationMode::SetDirectly); \
	DefStats->ModifyStatsUniformly(100, EStatValueType::BasePairs, EModificationMode::SetDirectly); \
	DefStats->RecalculateStats(true); \
	\
	/* Defending affinities */ \
	ADD_NEW_COMPONENT(UAffinitiesComponent, DefAffinities, DefActor); \
	FAffinity FightingAffinity = {}; \
	FightingAffinity.Type = Fighting; \
	FightingAffinity.SetCurrentPoints(1); \
	FAffinity FireAffinity = {}; \
	FireAffinity.Type = Fire; \
	FireAffinity.SetCurrentPoints(2); \
	DefAffinities->Affinities = {FightingAffinity, FireAffinity};
	
};