#pragma once
#include "CombatStatsComponent.h"
#include "StatUnitTestUtilities.generated.h"

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
	
};