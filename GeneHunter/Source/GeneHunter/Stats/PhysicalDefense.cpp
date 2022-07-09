#include "PhysicalDefense.h"

FSupportingText const UPhysicalDefense::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of physical damage a Monster can deal."),
		FText::FromString("Me strong krug!")
	};
	return SupportingText;
}

FString const UPhysicalDefense::Name() const
{
	const FString Name = FString{"Physical Attack"};
	return Name;
}

FString const UPhysicalDefense::Abbreviation() const
{
	const FString Abbrev = FString{"PhA"};
	return Abbrev;
}

FLinearColor const UPhysicalDefense::Color() const
{
	const FLinearColor Color = FLinearColor{0.4f, 0.546f, 1};
	return Color;
}