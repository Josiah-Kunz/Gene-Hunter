#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UtilityFunctionLibrary.generated.h"

/**
 * A library just for custom constants.
 */
UCLASS()
class BPLIBRARIES_API UUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

#pragma region Floats, strings, sig figs, and SI units
	
public:
	
	inline static const TArray<FString> IncPrefixes = {"k", "M", "G", "T", "P", "E", "Z", "Y"};
	inline static const TArray<FString> DecPrefixes = { "m", "μ", "n", "p", "f", "a", "z", "y" };

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void RangeToString(UPARAM(ref) const FFloatRange& Range, FString& Out);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float RoundToDecimals(const float Original, const int NumDecimals);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString FloatSigFigs(const float Value, const int NumSigFigs);
	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FText ToSI(const float Value, const int NumSigFigs, const bool bIntegerOnly = false);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float FromSI(FText Text);
	
};

#pragma endregion