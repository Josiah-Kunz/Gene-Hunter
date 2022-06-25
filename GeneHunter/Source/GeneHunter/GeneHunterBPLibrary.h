

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PanelWidget.h"
#include "GeneHunterBPLibrary.generated.h"


class UWidget;
/**
 * 
 */
UCLASS()
class GENEHUNTER_API UGeneHunterBPLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext = "uasset", const FString OldFilename = "");

	UFUNCTION(BlueprintCallable)
	static void SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted);

	UFUNCTION(BlueprintCallable)
	static bool SaveLoadedAssetFromAnywhere(UObject* Asset, const bool bOnlyIfDirty = true);

	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void ClearChildrenExcept(UPanelWidget* Widget, const TArray<UWidget*> Exclude);

	UFUNCTION(BlueprintCallable)
	static UWidget* Duplicate(const UWidget* Original);
	
	static constexpr int MAX_ITERATIONS = 10000;

	static UWidget* GetChildOfType(const UUserWidget* Parent, const class TSubclassOf<class UWidget> WidgetClass);
};
