
#include "GeneHunterBPLibrary.h"


void UGeneHunterBPLibrary::EnsureValidAssetName(const FString Filename, const FString Path, FString& SafeFilename, FString& AbsolutePath, const FString Ext, const FString OldFilename)
{
	SafeFilename = "";

	// Only alpha characters allowed!
	for (char c : Filename)
	{
		if (std::isalpha(c))
			SafeFilename += c;
	}

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
		NewFilename = Filename + "_" + FString::FromInt(i);
		if (NewFilename == OldFilename)
			break;
		bFoundFile= FPaths::FileExists(AbsolutePath + "/" + NewFilename + "." + Ext);
	}
	SafeFilename = NewFilename;
	
}

void UGeneHunterBPLibrary::SortAssetsAlphabetically(const TArray<FAssetData> Assets, TArray<FAssetData>& Sorted)
{
	Sorted = Assets;
	Sorted.Sort([](const FAssetData& A, const FAssetData& B)
	{
		return A.AssetName.LexicalLess(B.AssetName);
	});
}


