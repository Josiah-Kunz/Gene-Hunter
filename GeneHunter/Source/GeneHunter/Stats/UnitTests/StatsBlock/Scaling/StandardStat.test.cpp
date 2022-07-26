#pragma once

#include "GeneHunter/Stats/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Scaling_StandardStat,
	"UStat.StatsBlock.Scaling.Standard Stat",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Scaling_StandardStat::RunTest(const FString& Parameters)
{
	
	// Set up
	FStandardStat* StandardStat = {};

	// Loop over base pairs [1, 50, 100], base stat [0, 50, 100, 120, 150, 200], and levels [20, 50, 100]
	TArray<float> Expected = {
		// 1 BasePair
		// ----------
		// 0 BaseStat, levels [20, 50, 100]
		45, 1.2e3, 295.2e3,
		// 50 BaseStat
		99, 4.9e3, 2.1e6,
		// 100
		153, 8.7e3, 4e6,
		// 120
		180, 10.2e3, 4.7e6,
		// 150
		207, 12.6e3, 5.8e6,
		// 200
		270, 16.5e3, 7.7e6,

		// 50 BasePairs
		// ------------
		45, 1.2e3, 295.2e3,
		189, 11.4e3, 5.3e6,
		342, 21.6e3, 10.2e6,
		405, 25.5e3, 12.2e6,
		495, 31.8e3, 15.2e6,
		648, 42e3, 20.1e6,

		// 100 BasePairs (maximum)
		45, 1.2e3, 295.2e3,
		225, 13.4e3, 6.2e6,
		405, 25.5e3, 12.1e6,
		477, 30.4e3, 14.5e6,
		585, 37.7e3, 18e6,
		765, 49.8e3, 23.9e6
	};

	// Test bounds
	TArray<int> BasePairs = {1, 50, 100};
	TArray<int> BaseStats = {0, 50, 100, 120, 150, 200};
	TArray<int> Levels = {20, 50, 100};

	// Do the test
	for(int bp=0; bp<BasePairs.Num(); bp++)
	{
		StandardStat->BasePairs = BasePairs[bp];
		for(int bs=0; bs<BaseStats.Num(); bs++)
		{
			StandardStat->BaseStat = BaseStats[bs];
			for(int l=0; l<Levels.Num(); l++)
			{
				const float Actual = StandardStat->CalculateValue(Levels[l]);
				const float Tolerance = (Actual > 1e6 ? 0.1e6 : (Actual > 1e3 ? 0.1e3 : 1));
				TestEqual(
					FString::Printf(TEXT("BasePairs %s | BaseStat %s | Level %s"),
							*FString::FromInt(StandardStat->BasePairs),
							*FString::FromInt(StandardStat->BaseStat),
							*FString::FromInt(Levels[l])),
						Actual,
						Expected[bp * (Levels.Num() * BaseStats.Num()) + bs * Levels.Num() + l],
						Tolerance
					);
			}
		}
	}
	
	
	// Return
	return true;
}