#include "PhysicalAttack.h"

FSupportingText const* UPhysicalAttack::SupportingText() const
{
	const FSupportingText* SupportingText = new FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of physical damage a Monster can deal."),
		FText::FromString("Me strong krug!")
	};
	return SupportingText;
}

FString const* UPhysicalAttack::Name() const
{
	const FString* Name = new FString{"Physical Attack"};
	return Name;
}

FString const* UPhysicalAttack::Abbreviation() const
{
	const FString* Abbrev = new FString{"PhA"};
	return Abbrev;
}

FLinearColor const* UPhysicalAttack::Color() const
{
	const FLinearColor* Color = new FLinearColor{0.4f, 0.546f, 1};
	return Color;
}