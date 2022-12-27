#pragma once
#include "StatsComponent.h"
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
	UStatsComponent* StatsComponent; \
	StatsComponent = NewObject<UStatsComponent>(DummyActor); \
	StatsComponent->EnsureLevelComponent(DummyActor); \
	TArray<float> BaseStats = { 116, 100, 100, 60, 90, 50, 120}; \
	StatsComponent->ModifyStats(BaseStats, EStatValueType::BaseStat, EModificationMode::SetDirectly);

#define BASESTATS_GC \
	DummyWorld->DestroyWorld(false);
	
};