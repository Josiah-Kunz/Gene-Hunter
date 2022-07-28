#pragma once
#include "TypeArray1D.h"
#include "TypeArray2D.generated.h"

USTRUCT(BlueprintType)
struct TYPES_API FTypeArray2D : public FTypeArray1D
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<UType*> Array2 = {};

	/**
	 * Determines if SearchTarget is inside Container (by name).
	 */
	static bool Contains(const TArray<FTypeArray2D*>& Container, const FTypeArray2D* SearchTarget,
		FString& Description);

	/**
	 * Uses ArrayOfTypeArray1DsAreEqual.
	 */
	static bool ArrayOfTypeArray2DsAreEqual(const TArray<FTypeArray2D*>& Actual, const TArray<FTypeArray2D*>& Expected,
		FString& Description);

	/**
	 * Returns, e.g., "{[Air, Earth], [Fire, Water]}".
	 */
	static FString TypeArray2DToFString(const FTypeArray2D* TypeArray2D);
	
	/**
	 * Returns, e.g., "<{[Air, Earth], [Fire, Water]}, {[Flying, Ground], [Ice, Steel]}>". 
	 */
	static FString ArrayOfTypeArray2DToFString(const TArray<FTypeArray2D*>& ArrayOfTypeArray2D);
};