#pragma once

#include "CoreMinimal.h"

#include "StatRandParams.generated.h"

/**
 * A struct to hold information about randomizing stats.
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FStatRandParams
{
	GENERATED_BODY()

public:

	/** Inclusive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinBaseStat = 50;

	/** Inclusive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBaseStat = 150;

	/** Inclusive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MinBasePairs = 1;

	/** Inclusive. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxBasePairs = 100;
	
};
