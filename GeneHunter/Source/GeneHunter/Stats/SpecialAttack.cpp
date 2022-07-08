#include "SpecialAttack.h"

FSupportingText const* USpecialAttack::SupportingText() const
{
	const FSupportingText* SupportingText = new FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of special (non-physical) damage a Monster can deal."),
		FText::FromString("")
	};
	return SupportingText;
}

FString const* USpecialAttack::Name() const
{
	const FString* Name = new FString{"Special Attack"};
	return Name;
}

FString const* USpecialAttack::Abbreviation() const
{
	const FString* Abbrev = new FString{"SpA"};
	return Abbrev;
}

FLinearColor const* USpecialAttack::Color() const
{
	const FLinearColor* Color = new FLinearColor{0.718f, 0.443f, 0.957f};
	return Color;
}