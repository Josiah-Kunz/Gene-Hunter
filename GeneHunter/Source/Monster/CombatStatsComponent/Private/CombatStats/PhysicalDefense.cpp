#include "PhysicalDefense.h"

FSupportingText const FPhysicalDefense::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of physical toughness a Monster has."),
		FText::FromString("")
	};
	return SupportingText;
}

FString const FPhysicalDefense::Name() const
{
	const FString Name = FString{"Physical Defense"};
	return Name;
}

FString const FPhysicalDefense::Abbreviation() const
{
	const FString Abbrev = FString{"PhD"};
	return Abbrev;
}

FLinearColor const FPhysicalDefense::Color() const
{
	const FLinearColor Color = FLinearColor{0.957f, 0.443f, 0.443f};
	return Color;
}