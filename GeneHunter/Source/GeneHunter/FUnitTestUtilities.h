#pragma once
#include "Types/Type.h"
#include <algorithm>
#include "Types/UnitTests/DummyType.h"

class FUnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	/**
	 * Determines if SearchTarget is inside Container.
	 *	- If ByName is true, only compares by name.
	 *	- If ByName is false, compares via direct object comparison.
	 */
	static bool Contains(const TArray<UType*>& Container, const UType* SearchTarget, const bool bByName = true);

	static bool TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected, FString& Description);

	static bool ArraysOfTypeAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected, FString& Description);
	
	static bool TypeArray1sAreEqual(const FTypeArray1& Array1, const FTypeArray1& Array2, FString& Description);

	
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
