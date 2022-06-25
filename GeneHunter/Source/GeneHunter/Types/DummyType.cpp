// 


#include "DummyType.h"

#include "../GeneHunterBPLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"

/*
 * Gets the Type Assets (not the Types themselves).
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UDummyType::GetAllDummyAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC)
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
void UDummyType::GetAllDummyTypes(TArray<UDummyType*>& Types, const TArray<UType*> Exclude, const bool bSortABC)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllDummyAssets(Assets, bSortABC);
	for(FAssetData& Asset : Assets)
	{
		if (UDummyType* Type = Cast<UDummyType>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(Type))
				Types.Add(Type);
		}
	}
}

UDummyType* UDummyType::GetDummyTypeByName(const TArray<UDummyType*>& Pool, const FName Name)
{
	for(UDummyType* UTType : Pool)
	{
		if (UTType->GetFName() == Name)
			return UTType;
	}
	return nullptr;
}
