#pragma once

#include "Type.h"
#include "TypeArray1D.generated.h"

USTRUCT(BlueprintType)
struct TYPES_API FTypeArray1D
{

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY()
	TArray<UType*> Array = {};

	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<FTypeArray1D*>& Container, const FTypeArray1D* SearchTarget,
		const bool bByName = true); 


	/**
	 * Tests if two TypeArray1D are equal by simply checking if their FTypeArray1D.Array are equal.
	 */
	static bool TypeArray1DsAreEqual(const FTypeArray1D& Actual, const FTypeArray1D& Expected, FString& Description);


	/**
	 * Determines if
	 *	- Actual[i].Array[j] == Expected[k].Array[l]
	 *	
	 * for any i, j, k, l (by name comparison).
	 * 
	 *	- For example, [{A, B}, {a, b}] should equal [{b, a}, {A, B}]
	 */ 
	static bool ArrayOfTypeArray1DsAreEqual(const TArray<FTypeArray1D*>& Actual, const TArray<FTypeArray1D*>& Expected,
		FString& Description);

	/**
	 * Returns, e.g., "[Air, Earth, Fire, Water]".
	 */
	static FString TypeArray1DToFString(const FTypeArray1D* TypeArray1D);

	/**
	 * Returns, e.g., "{[Air, Earth], [Fire, Water]}".
	 */
	static FString ArrayOfTypeArray1DToFString(const TArray<FTypeArray1D*>& ArrayOfTypeArray1D);
	
};
