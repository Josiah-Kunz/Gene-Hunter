

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Components/PanelWidget.h"
#include "MathUtil.h"
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

	static constexpr int MAX_ITERATIONS = 10000;
	inline static const FString LINE_SEPARATOR = "=================================";

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static FString GetInfinityText();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float GetFloatInfinity();

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

	/**
	 * Works exactly like ClearChildren, but gives the option to exclude certain children.
	 */
	UFUNCTION(BlueprintCallable, meta = (AutoCreateRefTerm = "Exclude"))
	static void ClearChildrenExcept(UPanelWidget* Widget, const TArray<UWidget*> Exclude);

	/**
	 * Calls DuplicateObject with Outer as Original->GetOuter() (see official docs for further explanation).
	 */
	UFUNCTION(BlueprintCallable)
	static UWidget* Duplicate(const UWidget* Original);

	/**
	 *	Gets the first UWidget* of the specified class among the Parent's children.
	 *	Usage:
	 *		UButton* Button = Cast<UButton>(UGeneHunterBPLibrary::GetChildOfType(this, UButton::StaticClass()));
	 */
	UFUNCTION(BlueprintCallable)
	static UWidget* GetChildOfType(const UUserWidget* Parent, const TSubclassOf<UWidget> WidgetClass);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static void RangeToString(UPARAM(ref) const FFloatRange& Range, FString& Out);

	UFUNCTION(BlueprintCallable, BlueprintPure)
	static float RoundToDecimals(const float Original, const int NumDecimals);
	
};
