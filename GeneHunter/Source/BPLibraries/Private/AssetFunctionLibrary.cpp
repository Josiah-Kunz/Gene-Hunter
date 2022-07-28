#include "AssetFunctionLibrary.h"
#include "EditorAssetLibrary.h"

void UAssetFunctionLibrary::EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext, const FString OldFilename)
{
	// Debugging
	constexpr bool bDebug = false && GEngine;
	constexpr float DisplayTime = 15.0f;
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
		while (bFoundFile && i< UConstLibrary::MAX_ITERATIONS)
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

void UAssetFunctionLibrary::SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted)
{
	Sorted = Assets;
	Sorted.Sort([](const FAssetData& A, const FAssetData& B)
	{
		return A.AssetName.LexicalLess(B.AssetName);
	});
}

bool UAssetFunctionLibrary::SaveLoadedAssetFromAnywhere(UObject* Asset, const bool bOnlyIfDirty)
{
	return UEditorAssetLibrary::SaveLoadedAsset(Asset, bOnlyIfDirty);
}
