#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AssetRegistry/AssetData.h"
#include "AssetFunctionLibrary.generated.h"

/**
 * A library for the manipulation of assets.
 */
UCLASS()
class BPLIBRARIES_API UAssetFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	/**
	 * Determines a "safe" filename that is alphanumeric + "-" + "_" and is unique with the given Path. For example, takes "a 123 ??.txt" and returns "a123.txt".
	 *	- If it is not unique (for example, if there's already a file named "a123.txt"), counts up until it is unique (e.g., "a123_2.txt").
	 *	- It doesn't compare against itself, and hence the OldFilename is required.
	 */
	UFUNCTION(BlueprintCallable)
	static void EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename,
		FString& AbsolutePath, const FString Ext = "uasset", const FString OldFilename = "");

	UFUNCTION(BlueprintCallable)
	static void SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted);

	UFUNCTION(BlueprintCallable)
	static bool SaveLoadedAssetFromAnywhere(UObject* Asset, const bool bOnlyIfDirty = true);
};