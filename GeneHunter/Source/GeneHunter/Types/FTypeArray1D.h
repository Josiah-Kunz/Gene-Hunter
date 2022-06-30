#pragma once
#include "FTypeArray1D.generated.h"

// Forward declarations
class UType;

USTRUCT(BlueprintType)
struct FTypeArray1D
{

	GENERATED_USTRUCT_BODY()

public:
	TArray<UType*> Array = {};
};
