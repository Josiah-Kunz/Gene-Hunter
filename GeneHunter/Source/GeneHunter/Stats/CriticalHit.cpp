#include "CriticalHit.h"

float UCriticalHit::CalculateValue(const int Level)
{

	// Get prev- and next-decalevel data
	const float PrevDecaLevel = 10 * FMathf::Floor((Level + 0.1f)/10.0f);
	const float NextDecaLevel = 10 * FMathf::Ceil((Level + 0.1f)/10.0f);
	const float PrevSubCrit = SubCrit(PrevDecaLevel);
	const float NextSubCrit = SubCrit(NextDecaLevel);

	// Formuler
	return 0.8f * (NextSubCrit - PrevSubCrit) * (Level- PrevDecaLevel)/10.0f + PrevSubCrit;
}

FString const UCriticalHit::Name() const
{
	const FString Name = FString{"Haste"};
	return Name;
}

FString const UCriticalHit::Abbreviation() const
{
	const FString Abbrev = FString{"Hst"};
	return Abbrev;
}

FLinearColor const UCriticalHit::Color() const
{
	const FLinearColor Color = FLinearColor{0, 1, 1};
	return Color;
}

FSupportingText const UCriticalHit::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The higher this stat, the faster the Monster can use moves."),
		FText::FromString("")
	};
	return SupportingText;
}

float UCriticalHit::SubCrit(const int Level)
{
	return BaseStatScaling * FMathf::Pow(BaseStat, BaseStatExponent) *
		FMathf::Ceil(Level/10.0f) *
			FMathf::Pow(BasePairs/100, 0.25f) +
				LevelScaling * FMathf::Floor(Level/10.0f);
}