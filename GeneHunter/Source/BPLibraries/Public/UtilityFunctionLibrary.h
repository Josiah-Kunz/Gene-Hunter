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

#pragma region Effect delegate macros
	
public:

#define EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName) \
	TArray<F##BaseName##Delegate> Before##BaseName##Array ;\
	TArray<F##BaseName##Delegate> After##BaseName##Array ;

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_FourParams(BaseName, Param1, Param2, Param3, Param4) \
	DECLARE_DELEGATE_FourParams (F##BaseName##Delegate , Param1, Param2, Param3, Param4);\
	EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName)

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_ThreeParams(BaseName, Param1, Param2, Param3) \
	DECLARE_DELEGATE_ThreeParams (F##BaseName##Delegate , Param1, Param2, Param3);\
	EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName)

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_TwoParams(BaseName, Param1, Param2) \
	DECLARE_DELEGATE_TwoParams (F##BaseName##Delegate , Param1, Param2);\
	EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName)

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_OneParam(BaseName, Param1) \
	DECLARE_DELEGATE_OneParam (F##BaseName##Delegate , Param1);\
	EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName)

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES(BaseName) \
	DECLARE_DELEGATE (F##BaseName##Delegate );\
	EFFECT_DELEGATES_BEFORE_AND_AFTER_ARRAYS(BaseName)

#pragma endregion

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