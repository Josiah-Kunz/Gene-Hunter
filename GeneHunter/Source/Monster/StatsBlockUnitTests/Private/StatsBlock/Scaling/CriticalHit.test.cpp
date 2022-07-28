#pragma once

#include "StatUnitTestUtilities.h" 

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FUStat_StatsBlock_Scaling_CriticalHit,
	"UStat.StatsBlock.Scaling.Critical hit",
	EAutomationTestFlags::ApplicationContextMask | EAutomationTestFlags::ProductFilter)

bool FUStat_StatsBlock_Scaling_CriticalHit::RunTest(const FString& Parameters)
{
	
	// Set up
	FCriticalHit* CriticalHit = {};

	// Loop over base pairs [1, 50, 100], base stat [0, 50, 100, 120, 150, 200], and levels [20, 50, 100]
	TArray<float> Expected = {
		// 1 BasePair
		// ----------
		// 0 BaseStat, levels [20, 50, 100]
		1.2f, 3.1f, 6.2f,
		// 50 BaseStat
		1.3f, 3.2f, 6.4f,
		// 100
		1.8f, 4.6f, 9.1f,
		// 120
		2.5f, 6.2f, 12.4f,
		// 150
		4.4f, 11, 21.9f,
		// 200
		11.8f, 29.4f, 58.8f,

		// 50 BasePairs
		// ------------
		1.2f, 3.1f, 6.2f,
		1.3f, 3.3f, 6.7f,
		2.8f, 6.9f, 13.9f,
		4.5f, 11.3f, 22.6f,
		9.6f, 24, 48,
		29.2f, 73, 146,

		// 100 BasePairs (maximum)
		1.2f, 3.1f, 6.2f,
		1.3f, 3.4f, 6.7f,
		3.1f, 7.6f, 15.3f,
		5.1f, 12.8f, 25.7f,
		11.2f, 27.9f, 55.9f,
		34.5f, 86.2f, 172.4f
	};

	// Test bounds
	TArray<int> BasePairs = {1, 50, 100};
	TArray<int> BaseStats = {0, 50, 100, 120, 150, 200};
	TArray<int> Levels = {20, 50, 100};

	// Do the test
	for(int bp=0; bp<BasePairs.Num(); bp++)
	{
		CriticalHit->BasePairs = BasePairs[bp];
		for(int bs=0; bs<BaseStats.Num(); bs++)
		{
			CriticalHit->BaseStat = BaseStats[bs];
			for(int l=0; l<Levels.Num(); l++)
			{
				const float Actual = CriticalHit->CalculateValue(Levels[l]);
				const float Tolerance = (Actual > 1e6 ? 0.1e6 : (Actual > 1e3 ? 0.1e3 : 1));
				TestEqual(
					FString::Printf(TEXT("BasePairs %s | BaseStat %s | Level %s"),
							*FString::FromInt(CriticalHit->BasePairs),
							*FString::FromInt(CriticalHit->BaseStat),
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