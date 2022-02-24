
#include "GeneHunterBPLibrary.h"

#include "AssetRegistry/AssetRegistryModule.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Widget.h"
#include "EditorScriptingUtilities/Public/EditorAssetLibrary.h"

/*
 * Determines a "safe" filename that is alphanumeric + "-" + "_" and is unique with the given Path. For example, takes "a 123 ??.txt" and returns "a123.txt".
 *	- If it is not unique (for example, if there's already a file named "a123.txt"), counts up until it is unique (e.g., "a123_2.txt").
 *	- It doesn't compare against itself, and hence the OldFilename is required.
 */
void UGeneHunterBPLibrary::EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext, const FString OldFilename)
{

	// Debugging
	const bool bDebug = false && GEngine;
	const float DisplayTime = 15.0f;
	if (bDebug)
	{
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("[In] Filename: ") + Filename);
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("[In] OldFilename: ") + OldFilename); 
	}
	
	SafeFilename = "";

	// Only alphanumeric characters allowed!
	for (const char c : Filename)
	{
		if (std::isalnum(c) || c == '-' || c == '_')
			SafeFilename += c;
	}

	// Debug
	if (bDebug)
		GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("AlphaNumeric+ SafeFilename: ") + SafeFilename);
	

	// If the old name was already safe, by all means, keep it!
	if (SafeFilename != OldFilename)
	{
		// Make sure there aren't any duplicate asset names
		int i=1;
		FString NewFilename = SafeFilename;
		AbsolutePath =
				FPaths::ProjectContentDir() +
				FPaths::ConvertRelativePathToFull(Path).Replace(TEXT("/Game/"), TEXT(""));
		bool bFoundFile= FPaths::FileExists(AbsolutePath + "/" + NewFilename + "." + Ext);
		if (bDebug)
		{
			GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, FString::FromInt(i) + TEXT("st iteration NewFileName: ") + NewFilename);
			GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("Was it found at ")
				+ (AbsolutePath + "/" + NewFilename + "." + Ext) + TEXT("? " + (bFoundFile ? "Yes" : "No")));
		}
		while (bFoundFile && i<MAX_ITERATIONS)
		{
			i += 1;
			NewFilename = SafeFilename + "_" + FString::FromInt(i);
			if (bDebug)
				GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, FString::FromInt(i) + TEXT("th iteration NewFileName: ") + NewFilename);
			if (NewFilename == OldFilename)
				break;
			bFoundFile= FPaths::FileExists(AbsolutePath + "/" + NewFilename + "." + Ext);
		}
		SafeFilename = NewFilename;
		if (bDebug)
			GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("[Out] SafeFilename: ") + SafeFilename);
	} else
	{
		// Debug
		if (bDebug)
			GEngine->AddOnScreenDebugMessage(-1, DisplayTime, FColor::Cyan, TEXT("[Out] SafeFilename is the same as OldFilename."));
	}
}

void UGeneHunterBPLibrary::SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted)
{
	Sorted = Assets;
	Sorted.Sort([](const FAssetData& A, const FAssetData& B)
	{
		return A.AssetName.LexicalLess(B.AssetName);
	});
}

bool UGeneHunterBPLibrary::SaveLoadedAssetFromAnywhere(UObject* Asset, const bool bOnlyIfDirty)
{
	return UEditorAssetLibrary::SaveLoadedAsset(Asset, bOnlyIfDirty);
	
}

/*
 *	Deletes "None" entries in Type->AttackModifiers. This cannot be done by Blueprint methods (afaik).
 */
void UGeneHunterBPLibrary::PruneTypeAttackMods(UType* Type)
{

	// Vars
	TMap<UType*, FAttackModifier> OldMap(Type->AttackModifiers);

	// Clear and refill map
	Type->AttackModifiers.Empty();
	for(const TPair<UType*, FAttackModifier>& pair : OldMap)
	{
		if (pair.Key != nullptr)
			Type->AttackModifiers.Add(pair.Key, pair.Value);
	}
}

/*
 *	Gets the first UWidget* of the specified class among the Parent's children.
 *	Usage:
 *		UButton* Button = Cast<UButton>(UGeneHunterBPLibrary::GetChildOfType(this, UButton::StaticClass()));
 */
UWidget* UGeneHunterBPLibrary::GetChildOfType(const UUserWidget* Parent, const TSubclassOf<UWidget> WidgetClass)
{
	TArray<UWidget*> Children;
	Parent->WidgetTree->GetAllWidgets(Children);
	for(UWidget* Child : Children)
	{
		if(Child->IsA(WidgetClass))
			return Child;
	}
	return nullptr;
}

/*
 * Gets the Type Assets (not the Types themselves).
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UGeneHunterBPLibrary::GetAllTypeAssets(TArray<FAssetData>& TypeAssets, bool SortABC)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(TEXT("Type"), TypeAssets);
	if (SortABC)
		SortAssetsAlphabetically(TypeAssets, TypeAssets);
}

/*
 * Gets all Types.
 * @param Types The returned array filled with Types found in the assets (see GetAllTypeAssets).
 * @param Exclude A list of Types to exclude from this list.
 * @param SortABC If true, sorts the Types alphabetically. Make false to improve performance.
 */
void UGeneHunterBPLibrary::GetAllTypes(TArray<UType*>& Types, TArray<UType*> Exclude, bool SortABC)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllTypeAssets(Assets, SortABC);
	for(FAssetData& Asset : Assets)
	{
		if (UType* Type = Cast<UType>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(Type))
				Types.Add(Type);
		}
	}
}

/*
 * Works exactly like ClearChildren, but gives the option to exclude certain children.
 */
void UGeneHunterBPLibrary::ClearChildrenExcept(UPanelWidget* Widget, const TArray<UWidget*> Exclude)
{
	for(int i=Widget->GetChildrenCount() - 1; i>=0; i--)
	{
		if (!Exclude.Contains(Widget->GetChildAt(i)))
			Widget->RemoveChildAt(i);
	}
		
}




