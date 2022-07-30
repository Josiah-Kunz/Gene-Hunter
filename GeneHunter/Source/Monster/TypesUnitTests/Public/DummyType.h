#pragma once

#include "CoreMinimal.h"
#include "AssetFunctionLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Type.h"
#include "DummyType.generated.h"

/**
 * Since the UType class Type match-ups may change with balance testing, we need a static, never-changing "Type"-like
 * class that we can run through unit tests. This class serves to give reproducibility in such tests. 
 */
UCLASS()
class TYPESUNITTESTS_API UDummyType : public UType
{
	GENERATED_BODY()

public:

	/**
	 * A macro to get "dummy" Types. These are of type UDummyType and inherit from UType. These are independent of
	 *	in-game data (and hence are good for unit tests).
	 */
	#define GET_DUMMY_TYPES() \
		UWorld* World = UWorld::CreateWorld(EWorldType::Game, false); \
		TArray<UType*> AllDummyTypes; \
		UDummyType::GetAllDummyTypes(World, AllDummyTypes); \
		UType* Bug = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Bug-Dummy"))); \
		UType* Electric = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Electric-Dummy"))); \
		UType* Fighting = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fighting-Dummy"))); \
		UType* Fire = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Fire-Dummy"))); \
		UType* Flying = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Flying-Dummy"))); \
		UType* Grass = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Grass-Dummy"))); \
		UType* Ground = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ground-Dummy"))); \
		UType* Ice = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Ice-Dummy"))); \
		UType* Poison = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Poison-Dummy"))); \
		UType* Rock = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Rock-Dummy"))); \
		UType* Steel = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Steel-Dummy"))); \
		UType* Water = UDummyType::GetDummyTypeByName(AllDummyTypes, FName(TEXT("Water-Dummy")));

	#define GC_DUMMY_TYPES() \
		World->DestroyWorld(false); \
		CollectGarbage( GARBAGE_COLLECTION_KEEPFLAGS );
	
	static void GetAllDummyAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	static void GetAllDummyTypes(UWorld* World, TArray<UType*>& Types, const TArray<UType*> Exclude = {}, const bool bSortABC = false);

	static UType* GetDummyTypeByName(const TArray<UType*>& Pool, const FName Name);

};
