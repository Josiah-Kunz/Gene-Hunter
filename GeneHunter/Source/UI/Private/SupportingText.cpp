#include "SupportingText.h"

const TMap<FString, FString> FSupportingText::StaticReplacements = {
	{"\\CM", "sq"},
	{"\\SEC", "s"},
};

FText FSupportingText::DoReplacements(const FText& Text)
{

	// Convert for ease
	FString TextString = Text.ToString();
	
	for(const TPair<FString, FString>& KVP : StaticReplacements)
	{
		// Don't ignore case
		TextString.ReplaceInline(*KVP.Key, *KVP.Value);
	}

	// Convert back
	return FText::FromString(TextString);
}
