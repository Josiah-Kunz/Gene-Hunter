// 

#pragma once

#include "CoreMinimal.h"
#include "Type.h"
#include "DummyType.generated.h"

/**
 * Since the UType class Type matchups may change with balance testing, we need a static, never-changing "Type"-like
 * class that we can run through unit tests. This class serves to give reproducibility in such tests. 
 */
UCLASS()
class GENEHUNTER_API UDummyType : public UType
{
	GENERATED_BODY()

public:
	
	static void GetAllDummyAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	static void GetAllDummyTypes(TArray<UDummyType*>& Types, const TArray<UType*> Exclude = {}, const bool bSortABC = false);

	static UDummyType* GetDummyTypeByName(const TArray<UDummyType*>& Pool, const FName Name);
};
