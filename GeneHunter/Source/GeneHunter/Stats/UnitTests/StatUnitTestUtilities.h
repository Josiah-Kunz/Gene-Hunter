#pragma once
#include "GeneHunter/Stats/StatsBlock.h"
#include "Misc/AutomationTest.h"
#include "StatUnitTestUtilities.generated.h"

UCLASS()
class UStatUnitTestUtilities : public UBlueprintFunctionLibrary
{
public:

	GENERATED_BODY()
	
	constexpr static float TOLERANCE = 0.1F;
// TODO
#define DUMMY_BASE_STATS_BLOCK \
	UStatsBlock* StatsBlock = NewObject<UStatsBlock>(); /*\
	TMap<FStat&, int> BaseStatsMap; \
	BaseStatsMap.Add(StatsBlock->Health, 116); \
	BaseStatsMap.Add(StatsBlock->PhysicalAttack, 100); \
	BaseStatsMap.Add(StatsBlock->PhysicalDefense, 100); \
	BaseStatsMap.Add(StatsBlock->SpecialAttack, 60); \
	BaseStatsMap.Add(StatsBlock->SpecialDefense, 90); \
	BaseStatsMap.Add(StatsBlock->Haste, 50); \
	BaseStatsMap.Add(StatsBlock->CriticalHit, 120); \
	StatsBlock->ModifyStats(BaseStatsMap, EStatValueType::BaseStat, EModificationMode::SetDirectly);*/
	
};