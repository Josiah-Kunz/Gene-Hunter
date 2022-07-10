#include "Health.h"

float UHealth::CalculateValue(const int Level)
{
	return FMathf::Floor(2 * BaseStat * FMathf::Pow(BasePairs/100.0f, 0.25f) * Level/100.0f + 10) *
		StatJump(Level); 
}

FSupportingText const UHealth::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of damage a Monster can take."),
		FText::FromString("Blood for the blood god!")
	};
	return SupportingText;
}

FString const UHealth::Name() const
{
	const FString Name = FString{"Health"};
	return Name;
}

FString const UHealth::Abbreviation() const
{
	const FString Abbrev = FString{"HP"};
	return Abbrev;
}

FLinearColor const UHealth::Color() const
{
	const FLinearColor Color = FLinearColor{1, 0.5f, 1};
	return Color;
}
