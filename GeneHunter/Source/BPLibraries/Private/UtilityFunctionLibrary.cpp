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
