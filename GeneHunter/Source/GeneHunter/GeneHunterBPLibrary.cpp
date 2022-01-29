
#include "GeneHunterBPLibrary.h"
#include "EditorScriptingUtilities/Public/EditorAssetLibrary.h"

/*
 * Determines a "safe" filename that is alphanumeric + "-" + "_" and is unique with the given Path. For example, takes "a 123 ??.txt" and returns "a123.txt".
 *	- If it is not unique (for example, if there's already a file named "a123.txt"), counts up until it is unique (e.g., "a123_2.txt").
 *	- It doesn't compare against itself, and hence the OldFilename is required.
 */
void UGeneHunterBPLibrary::EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext, const FString OldFilename)
{
	SafeFilename = "";

	// Only alphanumeric characters allowed!
	for (const char c : Filename)
	{
		if (std::isalnum(c) || c == '-' || c == '_')
			SafeFilename += c;
	}

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
		while (bFoundFile && i<MAX_ITERATIONS)
		{
			i += 1;
			NewFilename = SafeFilename + "_" + FString::FromInt(i);
			if (NewFilename == OldFilename)
				break;
			bFoundFile= FPaths::FileExists(AbsolutePath + "/" + NewFilename + "." + Ext);
		}
		SafeFilename = NewFilename;
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




