#include "StandardStat.h"

float UStandardStat::CalculateValue(const int Level)
{
	return FMathf::Floor(2 * BaseStat * FMathf::Pow(BasePairs/100, 0.25f) * Level/100 + 5) *
		StatJump(Level); 
}