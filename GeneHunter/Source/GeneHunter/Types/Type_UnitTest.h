// 

#pragma once

#include "CoreMinimal.h"
#include "Type.h"
#include "Type_UnitTest.generated.h"

/**
 * Since the UType class Type matchups may change with balance testing, we need a static, never-changing "Type"-like
 * class that we can run through unit tests. This class serves to give reproducible in such tests. 
 */
UCLASS()
class GENEHUNTER_API UType_UnitTest : public UType
{
	GENERATED_BODY()

public:
	
	static void GetAllUTTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC = false);

	static void GetAllUTTypes(TArray<UType_UnitTest*>& Types, const TArray<UType*> Exclude = {}, const bool bSortABC = false);

	static UType_UnitTest* GetUTTypeByName(const TArray<UType_UnitTest*> Pool, const FName Name);
};
