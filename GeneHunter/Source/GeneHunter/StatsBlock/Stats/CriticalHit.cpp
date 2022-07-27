#include "CriticalHit.h"

float FCriticalHit::CalculateValue(const int Level)
{

	// Get prev- and next-decalevel data
	const float PrevDecaLevel = 10 * FMathf::Floor(UGeneHunterBPLibrary::RoundToDecimals((Level + 0.1f)/10.0f, 3));
	const float NextDecaLevel = 10 * FMathf::Ceil(UGeneHunterBPLibrary::RoundToDecimals((Level + 0.1f)/10.0f, 3));
	const float PrevSubCrit = SubCrit(PrevDecaLevel);
	const float NextSubCrit = SubCrit(NextDecaLevel);

	// Formuler
	return 0.8f * (NextSubCrit - PrevSubCrit) * (Level- PrevDecaLevel)/10.0f + PrevSubCrit;
}

FString const FCriticalHit::Name() const
{
	const FString Name = FString{"Critical Hit"};
	return Name;
}

FString const FCriticalHit::Abbreviation() const
{
	const FString Abbrev = FString{"Crt"};
	return Abbrev;
}

FLinearColor const FCriticalHit::Color() const
{
	const FLinearColor Color = FLinearColor{0.957f, 0.784f, 0.443f};
	return Color;
}

FSupportingText const FCriticalHit::SupportingText() const
{
	const FSupportingText SupportingText = FSupportingText{
		FText::FromString(""),
		FText::FromString("The chance a Monster has to deal extra damage. If over 100%, this stat instead increases the critical damage."),
		FText::FromString("")
	};
	return SupportingText;
}

float FCriticalHit::SubCrit(const int Level)
{
	return BaseStatScaling * FMathf::Pow(BaseStat*1.0f, BaseStatExponent) *
		FMathf::Ceil( UGeneHunterBPLibrary::RoundToDecimals(Level/10.0f, 3)) *
			FMathf::Pow(BasePairs/100.0f, 0.25f) +
				LevelScaling * FMathf::Floor( UGeneHunterBPLibrary::RoundToDecimals(Level/10.0f, 3));
}
