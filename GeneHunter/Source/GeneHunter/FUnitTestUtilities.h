#pragma once
#include "Types/Type_UnitTest.h"

class FUnitTestUtilities
{
public:
	
	constexpr static float TOLERANCE = 0.1F;

	static bool TArrayAreEqual(const TArray<UType*> Array1, const TArray<UType_UnitTest*> Array2, FString& Description);

	/**
	 * A macro to get \"dummy\" Types. These are of type UType_UnitTest and inherit from UType. These are independent of
	 *	in-game data (and hence are good for unit tests).
	 */
#define GET_DUMMY_TYPES() \
	TArray<UType_UnitTest*> AllDummyTypes; \
	UType_UnitTest::GetAllUTTypes(AllDummyTypes); \
	UType_UnitTest* Bug = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Bug"))); \
	UType_UnitTest* Electric = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Electric"))); \
	UType_UnitTest* Fighting = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fighting"))); \
	UType_UnitTest* Fire = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Fire"))); \
	UType_UnitTest* Flying = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Flying"))); \
	UType_UnitTest* Grass = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Grass"))); \
	UType_UnitTest* Ground = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ground"))); \
	UType_UnitTest* Ice = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Ice"))); \
	UType_UnitTest* Poison = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Poison"))); \
	UType_UnitTest* Rock = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Rock"))); \
	UType_UnitTest* Steel = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Steel"))); \
	UType_UnitTest* Water = UType_UnitTest::GetUTTypeByName(AllDummyTypes, FName(TEXT("Water"))); 
	
};
