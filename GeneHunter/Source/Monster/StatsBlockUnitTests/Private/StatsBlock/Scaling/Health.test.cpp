#pragma once

#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Scaling_Health,
	"UStat.StatsBlock.Scaling.Health",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Scaling_Health::RunTest(const FString& Parameters)
{
	
	// Set up
	FHealth* Health = {};

	// Loop over base pairs [1, 50, 100], base stat [0, 50, 100, 120, 150, 200], and levels [20, 50, 100]
	TArray<float> Expected = {
		// 1 BasePair
		// ----------
		// 0 BaseStat, levels [20, 50, 100]
		90, 2.4e3, 590.5e3,
		// 50 BaseStat
		144, 6.1e3, 2.4e6,
		// 100
		198, 10e3, 4.3e6,
		// 120
		225, 11.4e3, 5e6,
		// 150
		252, 13.9e3, 6.1e6,
		// 200
		315, 17.7e3, 8e6,

		// 50 BasePairs
		// ------------
		90, 2.4e3, 590.5e3,
		234, 12.6e3, 5.6e6,
		387, 22.8e3, 10.5e6,
		450, 26.7e3, 12.5e6,
		540, 33e3, 15.5e6,
		693, 43.3e3, 20.4e6,

		// 100 BasePairs (maximum)
		90, 2.4e3, 590.5e3,
		270, 14.6e3, 6.5e6,
		450, 26.7e3, 12.4e6,
		522, 31.6e3, 14.8e6,
		630, 38.9e3, 18.3e6,
		810, 51e3, 24.2e6
	};

	// Test bounds
	TArray<int> BasePairs = {1, 50, 100};
	TArray<int> BaseStats = {0, 50, 100, 120, 150, 200};
	TArray<int> Levels = {20, 50, 100};

	// Do the test
	for(int bp=0; bp<BasePairs.Num(); bp++)
	{
		Health->BasePairs = BasePairs[bp];
		for(int bs=0; bs<BaseStats.Num(); bs++)
		{
			Health->BaseStat = BaseStats[bs];
			for(int l=0; l<Levels.Num(); l++)
			{
				const float Actual = Health->CalculateValue(Levels[l]);
				const float Tolerance = (Actual > 1e6 ? 0.1e6 : (Actual > 1e3 ? 0.1e3 : 1));
				TestEqual(
					FString::Printf(TEXT("BasePairs %s | BaseStat %s | Level %s"),
							*FString::FromInt(Health->BasePairs),
							*FString::FromInt(Health->BaseStat),
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