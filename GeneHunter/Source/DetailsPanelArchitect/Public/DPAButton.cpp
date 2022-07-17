#include "DPAButton.h"

#define LOCTEXT_NAMESPACE "DPAButton"

/*
FDPAButton::FDPAButton(FText LabelText, TFunction<void> OnClicked_Raw)
{
	this->LabelText = LabelText;
	this->OnClicked_Raw = OnClicked_Raw;
	ConstructDefaultValues();
}*/

FDPAButton::FDPAButton(FText LabelText, UObject* BoundObject)
{
	this->LabelText = LabelText;
	this->Object = BoundObject;
	ConstructDefaultValues();
}

void FDPAButton::ConstructDefaultValues()
{

	// Texts n such
	if (CategoryName.IsEqual(""))
		CategoryName = "Buttons";
	ConstructDefaultFText(ButtonText, "ButtonText", "Go!");
	ConstructDefaultFText(LocalizedDisplayName, "CatName", CategoryName.ToString());
	ConstructDefaultFText(RowFilterString, "Keyword", ButtonText.ToString());
	
}

void FDPAButton::ConstructDefaultFText(FText& Text, const FString LocText1, const FString LocText2)
{
	/*
	if (Text.IsEmptyOrWhitespace())
		Text =  FText::Format(LOCTEXT("{0}", "{1}"), LocText1, LocText2);*/
}

#undef LOCTEXT_NAMESPACE