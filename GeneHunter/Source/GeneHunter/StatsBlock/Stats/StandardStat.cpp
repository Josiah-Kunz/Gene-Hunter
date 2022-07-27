#include "StandardStat.h"

float FStandardStat::CalculateValue(const int Level)
{
	return FMathf::Floor(
		UGeneHunterBPLibrary::RoundToDecimals(
			2 * BaseStat * FMathf::Pow(BasePairs/100.0f, 0.25f) * Level/100.0f + 5, 3)
			) * StatJump(Level);
}