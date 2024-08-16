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

	
};