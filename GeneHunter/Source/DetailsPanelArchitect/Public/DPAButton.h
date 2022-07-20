#pragma once

#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DPAButton.generated.h"

UCLASS()
class UDPAButton : public UObject
{

	GENERATED_BODY()
	
#pragma region Required public variables

public:

	/**
	 * The label that appears on the left side of the column. Suggested constructor is LOCTEXT("ButtonLabel", "YourLabelHere").
	 */
	FText LabelText;
	
	std::function<void(void)>* OnClicked_Raw;

#pragma endregion 

#pragma region Optional public variables

public:

	/**
	 * The text that appears over the button. The default value is LOCTEXT("ButtonText", "Go!").
	 */
	FText ButtonText;

	/**
	 * The category to either create or edit. Default is "Buttons".
	 */
	FName CategoryName;

	/**
	 *
	 */
	ECategoryPriority::Type CategoryPriority = ECategoryPriority::Important;
	
	/**
	 * By default, this is LOCTEXT("CatName", CategoryName).
	 */
	FText LocalizedDisplayName;

	/**
	 * By default, this is LOCTEXT("Keyword", ButtonText).
	 */
	FText RowFilterString;

	FSlateFontInfo LabelFont = IDetailLayoutBuilder::GetDetailFont();

#pragma endregion

#pragma region Public functions

public:
	
	void ConstructDefaultValues();

#pragma endregion

#pragma region Private utility functions

private:
	
	/**
	 * If Text is empty or whitespace, formats it to LOCTEXT(LocText1, LocText2).
	 */
	static void ConstructDefaultFText(FText& Text, const FString LocText1, const FString LocText2);

#pragma endregion
	
};
