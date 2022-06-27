#pragma once
#include "FTypeArray1.h"
#include "FTypeArray2.generated.h"

// Forward declarations
class UType;

USTRUCT(BlueprintType)
struct FTypeArray2 : public FTypeArray1
{

	GENERATED_USTRUCT_BODY()

public:
	TArray<UType*> TypeArray2 = {};
};
