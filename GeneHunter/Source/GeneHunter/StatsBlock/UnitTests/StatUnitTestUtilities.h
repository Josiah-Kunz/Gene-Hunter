#pragma once
#include "GeneHunter/StatsBlock/StatsBlock.h"
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
	UStatsBlock* StatsBlock = NewObject<UStatsBlock>(); \
	TArray<FStatModStruct> BaseStatsMap = { \
	     {StatsBlock->Health, 116}, \
	     {StatsBlock->PhysicalAttack, 100}, \
	     {StatsBlock->PhysicalDefense, 100}, \
	     {StatsBlock->SpecialAttack, 60}, \
	     {StatsBlock->SpecialDefense, 90}, \
	     {StatsBlock->Haste, 50}, \
	     {StatsBlock->CriticalHit, 120}}; \
	StatsBlock->ModifyStats(BaseStatsMap, EStatValueType::BaseStat, EModificationMode::SetDirectly);
	
};