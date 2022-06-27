#pragma once
#include "FTypeArray1.generated.h"

// Forward declarations
class UType;

USTRUCT(BlueprintType)
struct FTypeArray1
{

	GENERATED_USTRUCT_BODY()

public:
	TArray<UType*> TypeArray = {};
};
