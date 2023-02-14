#include "SpecialAttack.h"

FSupportingText const FSpecialAttack::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The amount of special (non-physical) damage a Monster can deal."),
		FText::FromString("")
	};
	return SupportingText;
}

FString const FSpecialAttack::Name() const
{
	const FString Name = FString{"Special Attack"};
	return Name;
}

FString const FSpecialAttack::Abbreviation() const
{
	const FString Abbrev = FString{"SpA"};
	return Abbrev;
}

FLinearColor const FSpecialAttack::Color() const
{
	const FLinearColor Color = FLinearColor{0.718f, 0.443f, 0.957f};
	return Color;
}