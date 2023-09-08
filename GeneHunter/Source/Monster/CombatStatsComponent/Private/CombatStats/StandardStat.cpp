#include "StandardStat.h"

#include "MathUtil.h"
#include "UtilityFunctionLibrary.h" // for using, e.g., RoundToDecimal

float FStandardStat::CalculateValue(const uint16 Level)
{
	return FMathf::Floor(
		UUtilityFunctionLibrary::RoundToDecimals(
			2 * BaseStat * FMathf::Pow(BasePairs/100.0f, 0.25f) * Level/100.0f + 5, 3)
			) * StatJump(Level);
}
