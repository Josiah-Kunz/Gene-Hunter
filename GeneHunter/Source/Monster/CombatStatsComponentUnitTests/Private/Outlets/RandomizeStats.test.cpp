#pragma once

#include "RandomizeBetterStats_UNITTEST.h"
#include "ComponentUtilities.h"
#include "CombatStat.h"
#include "CombatStatsComponent.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRandomizeStats,
                                 "__GeneHunter.Effects.Outlets.UCombatStatsComponent.RandomizeStats",
                                 EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FRandomizeStats::RunTest(const FString& Parameters)
{

	// Set up a dummy with a Level
	DUMMY_TEST_COMPONENT(UCombatStatsComponent, StatsComponent);
	
	// Attach effect
	ADD_NEW_COMPONENT(URandomizeBetterStats_UNITTEST, Effect, DummyActor);

	// Define value types we're interested in
	const TArray<EStatValueType> TestedValueTypes = {EStatValueType::BasePairs, EStatValueType::BaseStat};
	const TMap<const EStatValueType, const int32> MinValues =
		{
			{EStatValueType::BasePairs, Effect->MinBasePairs},
			{EStatValueType::BaseStat, Effect->MinBaseStat}
		};

	// Test ALL stats 10 times (surely this is enough!)
	for(int i=0; i<10; i++)
	{
		// Randomize the stats
		StatsComponent->RandomizeStats();

		// Check each stat + type combination
		for(const EStatEnum StatEnum : StatsComponent->StatsArray)
		{
			for(const EStatValueType ValueType :TestedValueTypes)
			{
				const float Value = StatsComponent->GetStat(StatEnum).GetValue(ValueType);
				const float MinValue = MinValues[ValueType];
				TestTrue(
					FString::Printf(TEXT("[%s] should be at least [%s], but is [%s] instead!"),
						*UEnum::GetValueAsString(StatEnum),
						*FString::SanitizeFloat(MinValue),
						*FString::SanitizeFloat(Value)
					),
					Value >= MinValue
				);
			}
		}
	}
	
	// GC
	DUMMY_TEST_GC
	
	return true;
}

