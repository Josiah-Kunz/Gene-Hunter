#pragma once
#include "Types/Type.h"
#include <algorithm>
#include "Types/UnitTests/DummyType.h"

class FTypeUnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<UType*>& Container, const UType* SearchTarget,
		const bool bByName = true);
	
	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<FTypeArray1*>& Container, const FTypeArray1* SearchTarget,
		const bool bByName = true);

	/**
	 * Tests if the arrays of Type* and DummyType* are equal (by name).
	 */
	static bool TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected,
		FString& Description);

	/**
	 * Tests if the arrays of Type* and Type* are equal (by name).
	 */
	static bool ArraysOfTypeAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected,
		FString& Description);

	/**
	 * Tests if two TypeArray1 are equal by simply checking if their FTypeArray1.TypeArray are equal.
	 */
	static bool TypeArray1sAreEqual(const FTypeArray1& Actual, const FTypeArray1& Expected, FString& Description);

	/**
	 * Determines if
	 *	- Actual[i].TypeArray[j] == Expected[k].TypeArray[l]
	 *	
	 * for any i, j, k, l (by name comparison).
	 * 
	 *	- For example, [{A, B}, {a, b}] should equal [{b, a}, {A, B}]
	 */ 
	static bool ArrayOfTypeArray1sAreEqual(const TArray<FTypeArray1*>& Actual, const TArray<FTypeArray1*>& Expected,
		FString& Description);

	/**
	 * Returns, e.g., "[Air, Earth, Fire, Water]".
	 */
	static FString TypeArray1ToFString(const FTypeArray1* TypeArray1);

	/**
	 * Returns, e.g., "{[Air, Earth], [Fire, Water]}".
	 */
	static FString ArrayOfTypeArray1ToFString(const TArray<FTypeArray1*>& ArrayOfTypeArray1);

	/**
	 * Performs "UType::Analyze" (assuming attackers) and returns if the result is equal to the expected values.
	 */
	static bool DoAttackAnalysis(const TArray<UType*>& AllTypes, const TArray<UType*>& Attackers, 
		const int NumDefendingTypes, const EAttackModifierMode Mode, const TArray<FTypeArray1*>& Expected,
		FString& Description);
	
	/**
	 * A macro to get "dummy" Types. These are of type UDummyType and inherit from UType. These are independent of
	 *	in-game data (and hence are good for unit tests).
	 */
#define GET_DUMMY_TYPES() \
	TArray<UDummyType*> AllDummyTypes; \
	UDummyType::GetAllDummyTypes(AllDummyTypes); \
	UDummyType* Bug = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Bug-Dummy"))); \
	UDummyType* Electric = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Electric-Dummy"))); \
	UDummyType* Fighting = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fighting-Dummy"))); \
	UDummyType* Fire = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fire-Dummy"))); \
	UDummyType* Flying = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Flying-Dummy"))); \
	UDummyType* Grass = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Grass-Dummy"))); \
	UDummyType* Ground = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ground-Dummy"))); \
	UDummyType* Ice = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ice-Dummy"))); \
	UDummyType* Poison = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Poison-Dummy"))); \
	UDummyType* Rock = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Rock-Dummy"))); \
	UDummyType* Steel = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Steel-Dummy"))); \
	UDummyType* Water = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Water-Dummy"))); 
	
};
