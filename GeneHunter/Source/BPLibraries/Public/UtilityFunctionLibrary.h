#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConstLibrary.h"
#include "MathUtil.h"
#include "UtilityFunctionLibrary.generated.h"

/**
 * A library just for custom constants.
 */
UCLASS()
class GENEHUNTER_API UUtilityFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void RangeToString(UPARAM(ref) const FFloatRange& Range, FString& Out);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float RoundToDecimals(const float Original, const int NumDecimals);
	
};