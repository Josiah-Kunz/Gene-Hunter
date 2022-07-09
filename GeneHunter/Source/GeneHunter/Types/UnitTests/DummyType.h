#pragma once

#include "CoreMinimal.h"
#include "GeneHunter/GeneHunterBPLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "GeneHunter/Types/Type.h"
#include "DummyType.generated.h"

/**
 * Since the UType class Type match-ups may change with balance testing, we need a static, never-changing "Type"-like
 * class that we can run through unit tests. This class serves to give reproducibility in such tests. 
 */
UCLASS()
class GENEHUNTER_API UDummyType : public UType
{
	GENERATED_BODY()

public:

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
	
	static void GetAllDummyAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	static void GetAllDummyTypes(TArray<UDummyType*>& Types, const TArray<UType*> Exclude = {}, const bool bSortABC = false);

	static UDummyType* GetDummyTypeByName(const TArray<UDummyType*>& Pool, const FName Name);

	/**
	 * Tests if the arrays of Type* and DummyType* are equal (by name).
	 */
	static bool TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected,
		FString& Description);
};
