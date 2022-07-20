#include "PhysicalDefense.h"

FSupportingText const UPhysicalDefense::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of physical toughness a Monster has."),
		FText::FromString("")
	};
	return SupportingText;
}

FString const UPhysicalDefense::Name() const
{
	const FString Name = FString{"Physical Defense"};
	return Name;
}

FString const UPhysicalDefense::Abbreviation() const
{
	const FString Abbrev = FString{"PhD"};
	return Abbrev;
}

FLinearColor const UPhysicalDefense::Color() const
{
	const FLinearColor Color = FLinearColor{0.4f, 0.546f, 1};
	return Color;
}