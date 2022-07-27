#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ConstLibrary.generated.h"

/**
 * A library just for custom constants.
 */
UCLASS()
class GENEHUNTER_API UConstLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	static constexpr int MAX_ITERATIONS = 10000;
	inline static const FString LINE_SEPARATOR = "=================================";

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString GetInfinityText(){return TEXT("∞");}

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetFloatInfinity(){return INFINITY;}
};