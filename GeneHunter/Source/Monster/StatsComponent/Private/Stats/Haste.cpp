#include "Haste.h"

#include "MathUtil.h"
#include "UtilityFunctionLibrary.h" // for using, e.g., RoundToDecimal

float FHaste::CalculateValue(const uint16 Level)
{
	const float BaseStatScaling = 0.00002f;
	const float LevelScaling = 0.017f;
	return Level * (
		BaseStatScaling * FMathf::Pow(BaseStat, 2) * FMathf::Pow(BasePairs/100.0f, 0.25f) +
		LevelScaling * FMathf::Floor( UUtilityFunctionLibrary::RoundToDecimals(Level/10.0f, 3))
	);
}

FString const FHaste::Name() const
{
	const FString Name = FString{"Haste"};
	return Name;
}

FString const FHaste::Abbreviation() const
{
	const FString Abbrev = FString{"Hst"};
	return Abbrev;
}

FLinearColor const FHaste::Color() const
{
	const FLinearColor Color = FLinearColor{0, 1, 1};
	return Color;
}

FSupportingText const FHaste::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The higher this stat, the faster the Monster can use moves."),
		FText::FromString("")
	};
	return SupportingText;
}