#include "DPAButton.h"

#define LOCTEXT_NAMESPACE "DPAButton"

void UDPAButton::ConstructDefaultValues()
{

	// Texts n such
	if (CategoryName.IsEqual(""))
		CategoryName = "Buttons";
	ConstructDefaultFText(ButtonText, "ButtonText", "Go!");
	ConstructDefaultFText(LocalizedDisplayName, "CatName", CategoryName.ToString());
	ConstructDefaultFText(RowFilterString, "Keyword", ButtonText.ToString());
	
}

void UDPAButton::ConstructDefaultFText(FText& Text, const FString LocText1, const FString LocText2)
{
	/*
	if (Text.IsEmptyOrWhitespace())
		Text =  FText::Format(LOCTEXT("{0}", "{1}"), LocText1, LocText2);*/
}

#undef LOCTEXT_NAMESPACE