#include "SpecialDefense.h"

FSupportingText const FSpecialDefense::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of special (non-physical) toughness a Monster has."),
		FText::FromString("")
	};
	return SupportingText;
}

FString const FSpecialDefense::Name() const
{
	const FString Name = FString{"Special Defense"};
	return Name;
}

FString const FSpecialDefense::Abbreviation() const
{
	const FString Abbrev = FString{"SpD"};
	return Abbrev;
}

FLinearColor const FSpecialDefense::Color() const
{
	const FLinearColor Color = FLinearColor{0.456f, 0.791f, 0.281f};
	return Color;
}