


#include "GeneHunterBPLibrary.h"


FString UGeneHunterBPLibrary::EnsureValidAssetName(const FString Filename)
{
	FString Ret = "";

	// Only alpha characters allowed!
	for (char c : Filename)
	{
		if (std::isalpha(c))
			Ret += c;
	}

	return Ret;
	
}

