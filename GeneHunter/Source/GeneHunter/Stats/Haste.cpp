#include "Haste.h"

float UHaste::CalculateValue(const int Level)
{
	const float BaseStatScaling = 0.00002f;
	const float LevelScaling = 0.017f;
	return Level * (
		BaseStatScaling * FMathf::Pow(BaseStat, 2) * FMathf::Pow(BasePairs/100, 0.25f) +
		LevelScaling * FMathf::Floor(Level/10)
	);
}

FString const UHaste::Name() const
{
	const FString Name = FString{"Haste"};
	return Name;
}

FString const UHaste::Abbreviation() const
{
	const FString Abbrev = FString{"Hst"};
	return Abbrev;
}

FLinearColor const UHaste::Color() const
{
	const FLinearColor Color = FLinearColor{0, 1, 1};
	return Color;
}

FSupportingText const UHaste::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The higher this stat, the faster the Monster can use moves."),
		FText::FromString("")
	};
	return SupportingText;
}