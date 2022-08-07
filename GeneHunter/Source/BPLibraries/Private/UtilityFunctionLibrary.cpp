#include "UtilityFunctionLibrary.h"

#include "ConstLibrary.h"
#include "MathUtil.h"
#include "Algo/Replace.h"

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

FString UUtilityFunctionLibrary::FloatSigFigs(const float Value, const int NumSigFigs)
{

	// Setup
	FString Ret = "";
	FString ValueString = FString::SanitizeFloat(Value);
	int SigFigs = 0;
	bool bDecimal = false;
	int ValueIndex = 0;
	int Failsafe = 0;

	// Go through entire string -or- until sigfigs are satisfied
	while(!bDecimal || SigFigs < NumSigFigs)
	{

		// Failsafe
		Failsafe++;
		if (Failsafe > UConstLibrary::MaxIterations)
		{
			UE_LOG(LogTemp, Warning, TEXT("Max iterations reached in UtilityFunctionLibrary::FloatSigFigs! Surely this is an error."))
			break;
		}
		
		// Check if we've hit the max number of sig figs. If so, we're searching for the decimal
		if (SigFigs >= NumSigFigs)
		{

			// Ran out of numbers? We must be done
			if (ValueIndex >= ValueString.Len())
				break;

			// Next is decimal; we're done
			if (ValueString[ValueIndex] == '.')
				break;
			
			// Add zeroes (not significant)
			Ret += '0';
			ValueIndex++;

			// Check if we've gone over the max length of "Value"
			// If ValueString == "1234" and we're at index 4, we've effectively run into a decimal.
			// If ValueString == "1.234" and we're at index 4, the decimal should already be accounted for.
			if (ValueIndex >= ValueString.Len())
				bDecimal = true; // This will end the loop
		} else
		{
			// Check that we have something to add
			if (ValueIndex < ValueString.Len()){

				// Check decimal
				if (ValueString[ValueIndex] == '.')
				{

					// Found it!
					bDecimal = true;

					// If we have enough sig figs, don't add the decimal (e.g., 1200 shouldn't be 1200.)
					if (SigFigs < NumSigFigs)
					{
						Ret += '.';
						ValueIndex++;
					}

				// Non-decimal
				} else
				{

					// Keep adding
					Ret += ValueString[ValueIndex];
					SigFigs++;
					ValueIndex++;

					// Should we add more decimals after this?
					if (SigFigs < NumSigFigs && ValueIndex >= ValueString.Len() && !bDecimal)
					{
						bDecimal = true;
						Ret += '.';
					}
				}
				
			// Ran out of numbers; add zeroes
			} else
			{
				Ret += '0';
				SigFigs++;

				// Should we add more decimals after this?
				if (SigFigs < NumSigFigs && ValueIndex >= ValueString.Len() && !bDecimal)
				{
					bDecimal = true;
					Ret += '.';
				}
			}
		}
	}
	return Ret;
}


FText UUtilityFunctionLibrary::ToSI(const float Value, const int NumSigFigs)
{
	FString StringValue = FString::SanitizeFloat(Value);

	// Trivial case
	if (StringValue == "0.0")
		return FText::FromString(StringValue);

	// Degree: 10^(3*Degree)
	// Scaled: just the number
	int Degree = FMath::RoundToInt(FMath::Floor(FMath::LogX(10, FMath::Abs(Value))/3));
	float Scaled = Value * FMathf::Pow(1000, -Degree);

	// No prefix
	if (0.001f < Value && Value < 1000)
		return FText::FromString(FloatSigFigs(Value, NumSigFigs));

	// Prefixes! YAY!
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
		if (0 < -Degree && -Degree < DecPrefixes.Num())
			Prefix = DecPrefixes[-Degree - 1];
		else
			Prefix = "ᴇ" + (-Degree * 3);
		break;
	case 0:
		return FText::FromString("0");
	}

	// Round depending on number of sig figs
	int NumDecimals = 0;
	if (Scaled < 1)
		NumDecimals = NumSigFigs;
	else if (Scaled < 10)
		NumDecimals = NumSigFigs - 1;
	else
		NumDecimals = NumSigFigs - 2; // If > 999, another prefix takes over
	
	return FText::FromString(
		FString::Printf(TEXT("%s%s"),
				//*FString::SanitizeFloat(RoundToDecimals(Scaled, NumDecimals)),
				*FloatSigFigs(Scaled, NumSigFigs),
				*Prefix
			)
		);
}

float UUtilityFunctionLibrary::FromSI(FText Text)
{

	// Setup
	FString String = Text.ToString();
	float Multiplier = 1;
	FString ReplacementZeros = "";

	// Increases
	for(int i=0; i<IncPrefixes.Num(); i++)
	{
		if (String.Contains(IncPrefixes[i]))
		{
			Multiplier *= FMathf::Pow(10, 3*(i+1));
			String = String.Replace(*IncPrefixes[i], *FString(""));
		}
	}

	// Decreases
	for(int i=0; i<DecPrefixes.Num(); i++)
	{
		if (String.Contains(DecPrefixes[i]))
		{
			Multiplier *= FMathf::Pow(10, -3*(i+1));
			String = String.Replace(*DecPrefixes[i], *FString(""));
		}
	}

	// Return
	return FCString::Atof(*String) * Multiplier;
}
