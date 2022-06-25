#pragma once
#include "Types/DummyType.h"

class FUnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	static bool TArrayAreEqual(const TArray<UType*> Array1, const TArray<UDummyType*> Array2, FString& Description);

	/**
	 * A macro to get "dummy" Types. These are of type UDummyType and inherit from UType. These are independent of
	 *	in-game data (and hence are good for unit tests).
	 */
#define GET_DUMMY_TYPES() \
	TArray<UDummyType*> AllDummyTypes; \
	UDummyType::GetAllDummyTypes(AllDummyTypes); \
	UDummyType* Bug = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Bug"))); \
	UDummyType* Electric = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Electric"))); \
	UDummyType* Fighting = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fighting"))); \
	UDummyType* Fire = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fire"))); \
	UDummyType* Flying = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Flying"))); \
	UDummyType* Grass = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Grass"))); \
	UDummyType* Ground = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ground"))); \
	UDummyType* Ice = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ice"))); \
	UDummyType* Poison = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Poison"))); \
	UDummyType* Rock = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Rock"))); \
	UDummyType* Steel = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Steel"))); \
	UDummyType* Water = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Water"))); 
	
};
