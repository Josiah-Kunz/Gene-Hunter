#include "FDPAButton.h"

#define LOCTEXT_NAMESPACE "FDPAButton"

FDPAButton::FDPAButton(const std::function<void()> OnClick, const FString ButtonText, const FString LabelText)
{
	this->OnClicked_Raw = OnClick;
	this->ButtonText = FText::FromString(ButtonText);
	this->LabelText = FText::FromString(LabelText);
}

void FDPAButton::ConstructDefaultValues()
{

	LabelFont =  IDetailLayoutBuilder::GetDetailFont();

	// Texts n such
	if (CategoryName.IsEqual(""))
		CategoryName = "Buttons";
	ConstructDefaultFText(ButtonText, "Go!");
	ConstructDefaultFText(LocalizedDisplayName, CategoryName.ToString());
	ConstructDefaultFText(RowFilterString, ButtonText.ToString());
}

void FDPAButton::ConstructDefaultFText(FText& Text, const FString DefaultValue)
{
	if (Text.IsEmptyOrWhitespace())
		Text =  FText::FromString(DefaultValue);
}

#undef LOCTEXT_NAMESPACE