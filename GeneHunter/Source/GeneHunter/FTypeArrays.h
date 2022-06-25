#pragma once
#include "FTypeArrays.generated.h"

// Forward declarations
class UType;

USTRUCT(BlueprintType)
struct FTypeArrays
{

	GENERATED_USTRUCT_BODY()
	
	TArray<UType*> TypeArray1 = {};
	TArray<UType*> TypeArray2 = {};
};
