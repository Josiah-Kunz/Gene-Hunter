// 


#include "Type_UnitTest.h"

#include "GeneHunterBPLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"

/*
 * Gets the Type Assets (not the Types themselves).
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UType_UnitTest::GetAllUTTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(TEXT("Type_UnitTest"), TypeAssets, false);
	if (bSortABC)
		UGeneHunterBPLibrary::SortAssetsAlphabetically(TypeAssets, TypeAssets);
}

/*
 * Gets all Types.
 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
 * @param Exclude A list of Types to exclude from this list.
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UType_UnitTest::GetAllUTTypes(TArray<UType_UnitTest*>& Types, const TArray<UType*> Exclude, const bool bSortABC)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllUTTypeAssets(Assets, bSortABC);
	for(FAssetData& Asset : Assets)
	{
		if (UType_UnitTest* Type = Cast<UType_UnitTest>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(Type))
				Types.Add(Type);
		}
	}
}

UType_UnitTest* UType_UnitTest::GetUTTypeByName(const TArray<UType_UnitTest*> Pool, const FName Name)
{
	for(UType_UnitTest* UTType : Pool)
	{
		if (UTType->GetFName() == Name)
			return UTType;
	}
	return nullptr;
}
