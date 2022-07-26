#include "Health.h"

float FHealth::CalculateValue(const int Level)
{
	return FMathf::Floor(
		UGeneHunterBPLibrary::RoundToDecimals(
			2 * BaseStat * FMathf::Pow(BasePairs/100.0f, 0.25f) * Level/100.0f + 10, 3)
			) * StatJump(Level); 
}

FSupportingText const FHealth::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of damage a Monster can take."),
		FText::FromString("Blood for the blood god!")
	};
	return SupportingText;
}

FString const FHealth::Name() const
{
	const FString Name = FString{"Health"};
	return Name;
}

FString const FHealth::Abbreviation() const
{
	const FString Abbrev = FString{"HP"};
	return Abbrev;
}

FLinearColor const FHealth::Color() const
{
	const FLinearColor Color = FLinearColor{1, 0.5f, 1};
	return Color;
}
