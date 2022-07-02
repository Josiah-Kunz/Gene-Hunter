#pragma once
#include "DummyType.h"


/*
 * Gets the Type Assets (not the Types themselves).
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UDummyType::GetAllDummyAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(TEXT("DummyType"), TypeAssets, false);
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
	for(UDummyType* DummyType : Pool)
	{
		if (DummyType->GetFName() == Name)
			return DummyType;
	}
	return nullptr;
}

bool UDummyType::TypesAndDummiesAreEqual(const TArray<UType*>& Actual, const TArray<UDummyType*>& Expected, FString& Description)
{
	
	// UDummyType* -> UType*
	TArray<UType*> ExpectedTypes;
	for(UDummyType* Dummy : Expected)
		if (UType* Type = Cast<UType>(Dummy))
			ExpectedTypes.Add(Type);

	// Pass to UType* comparison function
	return ArraysOfTypeAreEqual(Actual, ExpectedTypes, Description);

}