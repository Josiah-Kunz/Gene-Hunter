#include "UtilityFunctionLibrary.h"

#include "ConstLibrary.h"
#include "MathUtil.h"

void UUtilityFunctionLibrary::RangeToString(const FFloatRange& Range, FString& Out)
{
	// Get parens
	const FString LowerParen = Range.GetLowerBound().IsInclusive() ? "[" : "(";
	const FString UpperParen = Range.GetLowerBound().IsInclusive() ? "]" : ")";

	// Get parentheticals
	const FString LowerParenthetical = Range.GetLowerBound().IsClosed() ?
		FString::SanitizeFloat(Range.GetLowerBound().GetValue()) :
		UConstLibrary::GetInfinityText();
	const FString UpperParenthetical = Range.GetUpperBound().IsClosed() ?
		FString::SanitizeFloat(Range.GetUpperBound().GetValue()) :
		UConstLibrary::GetInfinityText();

	// Return
	Out = FString::Printf(TEXT("%s%s -- %s%s"),
		*LowerParen,
		*LowerParenthetical,
		*UpperParenthetical,
		*UpperParen
		);
}

float UUtilityFunctionLibrary::RoundToDecimals(const float Original, const int NumDecimals)
{
	const float PowerOfTen = FMathf::Pow(10, NumDecimals);
	return FMathf::Round( PowerOfTen * Original) / PowerOfTen;
}

FText UUtilityFunctionLibrary::ToSI(const float Value, const int NumDecimals)
{
	FString StringValue = FString::SanitizeFloat(Value);

	// Trivial case
	if (StringValue == "0")
		return FText::FromString(StringValue);

	// No prefix
	if (0.001f < Value && Value < 1000)
		return FText::FromString(
				FString::SanitizeFloat(
						FMath::RoundToInt(Value)
					)
			);

	// Prefixes! YAY!
	TArray<FString> IncPrefixes = {"k", "M", "G", "T", "P", "E", "Z", "Y"};
	TArray<FString> DecPrefixes = { "m", "μ", "n", "p", "f", "a", "z", "y" };
	int Degree = FMath::RoundToInt(FMath::Floor(FMath::LogX(10, FMath::Abs(Value))/3));
	float Scaled = Value * FMathf::Pow(1000, -Degree);

	FString Prefix = "";
	switch(FMath::Sign(Degree))
	{
	case 1:
		if (0 < Degree && Degree < IncPrefixes.Num())
			Prefix = IncPrefixes[Degree - 1];
		else
			Prefix = "ᴇ+" + (Degree * 3);
		break;
	case -1:
		if (0 < Degree && Degree < DecPrefixes.Num())
			Prefix = DecPrefixes[Degree - 1];
		else
			Prefix = "ᴇ" + (Degree * 3);
		break;
	case 0:
		return FText::FromString("0");
	}

	return FText::FromString(
		FString::Printf(TEXT("%s%s"),
				*FString::SanitizeFloat(RoundToDecimals(Scaled, NumDecimals)),
				*Prefix
			)
		);
}
