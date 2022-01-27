

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "EditorScriptingUtilities/Public/EditorAssetLibrary.h"
#include "GeneHunterBPLibrary.generated.h"


/**
 * 
 */
UCLASS()
class GENEHUNTER_API UGeneHunterBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(BlueprintCallable)
	static void EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext = "uasset", const FString OldFilename = "");

	UFUNCTION(BlueprintCallable)
	static void SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted);

	UFUNCTION(BlueprintCallable)
	static bool SaveLoadedAssetFromAnywhere(UObject* Asset, const bool bOnlyIfDirty = true);
	
public:
	static const int MAX_ITERATIONS = 10000;
};
