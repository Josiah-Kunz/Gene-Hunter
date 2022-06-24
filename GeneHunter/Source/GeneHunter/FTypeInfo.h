#pragma once
#include "FTypeInfo.generated.h"

// Forward dclarations
class UType;

USTRUCT(BlueprintType)
struct FTypeInfo
{

	GENERATED_USTRUCT_BODY()
	
	TArray<UType*> TypeArray1 = {};
	TArray<UType*> TypeArray2 = {};
};
