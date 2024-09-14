#include "MoveData.h"

#include "AssetFunctionLibrary.h"
#include "ProjectileMove.h"

UMoveData::UMoveData()
{
	SetCanDoDamage();
}

void UMoveData::GetAllMoveDataAssets(TArray<FAssetData>& MoveDataAssets, const bool bSortABC,
                                     const bool bIncludeDummy, const bool bIncludeReal)
{

	// Get the assets
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(UMoveData::StaticClass()->GetClassPathName(), MoveDataAssets, false);

	// Remove dummies or reals
	for(int i=MoveDataAssets.Num() - 1; i>=0; i--)
	{
		const bool bIsDummy = MoveDataAssets[i].AssetName.ToString().Contains(DUMMY_IDENTIFIER);
		if (!bIncludeDummy && bIsDummy)
		{
			MoveDataAssets.RemoveAt(i);
			continue;
		}

		if (!bIncludeReal && !bIsDummy)
		{
			MoveDataAssets.RemoveAt(i);
			continue;
		}
	}

	// Sort
	if (bSortABC)
	{
		UAssetFunctionLibrary::SortAssetsAlphabetically(MoveDataAssets, MoveDataAssets);
	}
}

void UMoveData::GetAllMoveData(TArray<UMoveData*>& MoveDataArray, const bool bSortABC, const bool bDummyOnly)
{
	GetAllMoveData(MoveDataArray, {}, bSortABC, bDummyOnly);
}

void UMoveData::GetAllMoveData(TArray<UMoveData*>& MoveDataArray, const TArray<UMoveData*>& Exclude,
		const bool bSortABC, const bool bDummyOnly)
{
	MoveDataArray.Empty();
	TArray<FAssetData> Assets;
	GetAllMoveDataAssets(Assets, bSortABC, bDummyOnly, !bDummyOnly);
	for(FAssetData& Asset : Assets)
	{

		// Check cast
		if (UMoveData* MoveData = Cast<UMoveData>(Asset.GetAsset()))
		{

			// Check exclusions, nullptr
			if (MoveData == nullptr || Exclude.Contains(MoveData))
				continue;

			// Dummy or nah?
			if (bDummyOnly)
			{
				if (MoveData->GetName().Contains(DUMMY_IDENTIFIER))
					MoveDataArray.Add(MoveData);
			} else
			{
				MoveDataArray.Add(MoveData);
			}
		}
	}
}

UMoveData* UMoveData::GetMoveDataByName(const TArray<UMoveData*>& Pool, const FName Name)
{
	for(UMoveData* MoveData : Pool)
		if (MoveData->GetFName() == Name)
		{
			return MoveData;
		}
	return nullptr;
}

FText UMoveData::GetDisplayName()
{
	if (DisplayName.IsEmptyOrWhitespace())
	{
		return FText::FromString(GetName());
	}
	return DisplayName;
}

#if WITH_EDITOR

void UMoveData::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);
	const FName PropertyName = (PropertyChangedEvent.Property != nullptr) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMoveData, Category))
	{
		SetCanDoDamage();
	}
}

void UMoveData::SetCanDoDamage()
{
	bCanDoDamage = (Category == EMoveCategory::PhysicalDamage || 
				   Category == EMoveCategory::SpecialDamage || 
				   Category == EMoveCategory::SpecialHealing);
}

#endif
