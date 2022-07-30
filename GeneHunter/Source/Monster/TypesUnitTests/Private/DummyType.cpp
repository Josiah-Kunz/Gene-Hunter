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
 * Gets all "Dummy" Types and replaces them with equivalent UTypes bound to the World.
 * Note: these *MUST* be garbage collected manually when you're done, preferably with World->DestroyWorld(false) and
 * CollectGarbage( GARBAGE_COLLECTION_KEEPFLAGS ) 
 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
 * @param Exclude A list of Types to exclude from this list.
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UDummyType::GetAllDummyTypes(UWorld* World, TArray<UType*>& Types, const TArray<UType*> Exclude, const bool bSortABC)
{

	// Get assets
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllDummyAssets(Assets, bSortABC);
	TArray<UDummyType*> DummyTypes;

	// Create UType equivalents bound to World
	for(FAssetData& Asset : Assets)
	{
		if (UDummyType* DummyType = Cast<UDummyType>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(DummyType))
			{
				UType* NewType = NewObject<UType>(World);
				NewType->Rename(*DummyType->GetName(), World);
				//NewType->AttackModifiers = Type->AttackModifiers;
				Types.Add(NewType);
				DummyTypes.Add(DummyType);
			}
		}
	}

	// Update attack modifiers
	for(int i=0; i<Types.Num();i++)
	{
		for(const TPair<UType*, FAttackModifier>& Pair : DummyTypes[i]->AttackModifiers)
		{
			Types[i]->AttackModifiers.Add(GetDummyTypeByName(Types,  FName(*Pair.Key->GetName())), Pair.Value);
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