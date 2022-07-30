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
		UAssetFunctionLibrary::SortAssetsAlphabetically(TypeAssets, TypeAssets);
}

/*
 * Gets all "Dummy" Types and converts them to UTypes. Note: these *MUST* be garbage collected manually when you're done!
 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
 * @param Exclude A list of Types to exclude from this list.
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UDummyType::GetAllDummyTypes(UWorld* World, TArray<UType*>& Types, const TArray<UType*> Exclude, const bool bSortABC)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllDummyAssets(Assets, bSortABC);
	UObject* Outer = (UObject*)GetTransientPackage();
	for(FAssetData& Asset : Assets)
	{
		if (UType* Type = Cast<UType>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(Type))
			{
				UType* NewType = NewObject<UType>(World);
				NewType->AttackModifiers = Type->AttackModifiers;
				Types.Add(NewType);
			}
		}
	}
}

UType* UDummyType::GetDummyTypeByName(const TArray<UType*>& Pool, const FName Name)
{
	for(UType* Type : Pool)
	{
		if (Type->GetFName() == Name)
			return Type;
	}
	return nullptr;
}