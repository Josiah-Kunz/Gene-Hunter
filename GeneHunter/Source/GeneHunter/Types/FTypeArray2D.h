#pragma once
#include "FTypeArray1D.h"
#include "FTypeArray2D.generated.h"

// Forward declarations
class UType;

USTRUCT(BlueprintType)
struct FTypeArray2D : public FTypeArray1D
{

	GENERATED_USTRUCT_BODY()

public:
	TArray<UType*> Array2 = {};
};