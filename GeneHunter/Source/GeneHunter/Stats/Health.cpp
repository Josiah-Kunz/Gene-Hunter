#include "Health.h"

float UHealth::CalculateValue(const int Level)
{
	return FMathf::Floor(2 * BaseStat * FMathf::Pow(BasePairs/100, 0.25f) * Level/100 + 10) *
		StatJump(Level); 
}

FSupportingText const* UHealth::SupportingText() const
{
	const FSupportingText* SupportingText = new FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of damage a Monster can take."),
		FText::FromString("Blood for the blood god!")
	};
	return SupportingText;
}

FString const* UHealth::Name() const
{
	const FString* Name = new FString{"Health"};
	return Name;
}

FString const* UHealth::Abbreviation() const
{
	const FString* Abbrev = new FString{"HP"};
	return Abbrev;
}

FLinearColor const* UHealth::Color() const
{
	const FLinearColor* Color = new FLinearColor{1, 0.5f, 1};
	return Color;
}
