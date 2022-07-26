#pragma once

#include "GeneHunter/Stats/UnitTests/StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Scaling_Haste,
	"UStat.StatsBlock.Scaling.Haste",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Scaling_Haste::RunTest(const FString& Parameters)
{
	
	// Set up
	FHaste* Haste = {};

	// Loop over base pairs [1, 50, 100], base stat [0, 50, 100, 120, 150, 200], and levels [20, 50, 100]
	TArray<float> Expected = {
		// 1 BasePair
		// ----------
		// 0 BaseStat, levels [20, 50, 100]
		0.7f, 4.2f, 17,
		// 50 BaseStat
		1, 5, 18.6f,
		// 100
		1.9f, 7.4f, 23.3f,
		// 120
		2.5f, 8.8f, 26.1f,
		// 150
		3.5f, 11.4f, 31.2f,
		// 200
		5.7f, 16.9f, 42.3f,

		// 50 BasePairs
		// ------------
		0.7f, 4.2f, 17,
		1.5f, 6.4f, 21.2f,
		4, 12.7f, 33.8f,
		5.5f, 16.4f, 41.2f,
		8.2f, 23.2f, 54.8f,
		14.1f, 37.9f, 84.3f,

		// 100 BasePairs (maximum)
		0.7f, 4.2f, 17,
		1.7f, 6.8f, 22,
		4.7f, 14.3f, 37,
		6.4f, 18.7f, 45.8f,
		9.7f, 26.8f, 62,
		16.7f, 44.2f, 97
	};

	// Test bounds
	TArray<int> BasePairs = {1, 50, 100};
	TArray<int> BaseStats = {0, 50, 100, 120, 150, 200};
	TArray<int> Levels = {20, 50, 100};

	// Do the test
	for(int bp=0; bp<BasePairs.Num(); bp++)
	{
		Haste->BasePairs = BasePairs[bp];
		for(int bs=0; bs<BaseStats.Num(); bs++)
		{
			Haste->BaseStat = BaseStats[bs];
			for(int l=0; l<Levels.Num(); l++)
			{
				const float Actual = Haste->CalculateValue(Levels[l]);
				const float Tolerance = (Actual > 1e6 ? 0.1e6 : (Actual > 1e3 ? 0.1e3 : 1));
				TestEqual(
					FString::Printf(TEXT("BasePairs %s | BaseStat %s | Level %s"),
							*FString::FromInt(Haste->BasePairs),
							*FString::FromInt(Haste->BaseStat),
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