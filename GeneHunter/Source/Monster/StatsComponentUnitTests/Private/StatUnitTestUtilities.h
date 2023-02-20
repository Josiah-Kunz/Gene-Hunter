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
	UWorld* DummyWorld = UWorld::CreateWorld(EWorldType::Game, false); \
	AActor* DummyActor = DummyWorld->SpawnActor(AActor::StaticClass()); \
	UCombatStatsComponent* StatsComponent = NewObject<UCombatStatsComponent>(DummyActor); \
	StatsComponent->RegisterComponent(); \
	StatsComponent->EnsureLevelComponent(DummyActor); \
	StatsComponent->LevelComponent->SetLevel(1); \
	TArray<float> BaseStats = { 116, 100, 100, 60, 90, 50, 120}; \
	StatsComponent->ModifyStats(BaseStats, EStatValueType::BaseStat, EModificationMode::SetDirectly); \
	StatsComponent->RecalculateStats(true);

#define BASESTATS_GC \
	DummyWorld->DestroyWorld(false);
	
};