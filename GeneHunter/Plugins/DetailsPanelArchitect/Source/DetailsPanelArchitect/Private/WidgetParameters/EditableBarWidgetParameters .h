#pragma once
#include "BarWidgetParameters.h"
#include "EditableTextBoxWidgetParameters.h"
#include "TextWidgetParameters.h"

struct FEditableBarWidgetParameters
{
public:

#pragma region Non-default values

	// Label
	FText LabelText;
	FText LabelTooltip;

	// EditableTextBox
	FText EditableTextBoxText;
	TFunction<void (const FText&, ETextCommit::Type&)> OnTextCommitted;

	// Slash
	// NONE!
	
	// Max
	FText MaxText;
	FText MaxTooltip;
	
	// Bar
	FLinearColor BarColor;
	float BarFraction;
	FText BarTooltip;

#pragma endregion

#pragma region Default values

	// Label
	FVector2D LabelSize = FVector2D{30, 20};
	FVector2D LabelPosition = FVector2D{0, 0};
	EHorizontalAlignment LabelHAlign = HAlign_Left;
	EVerticalAlignment LabelVAlign = VAlign_Center;

	// EditableTextBox
	FText EditableTextBoxTooltip = FText::GetEmpty();
	FVector2D EditableTextBoxSize = FVector2D{50+8, 20};
	FVector2D EditableTextBoxPosition = FVector2D{30, 0};
	EHorizontalAlignment EditableTextBoxHAlign = HAlign_Left;
	EVerticalAlignment EditableTextBoxVAlign = VAlign_Center;

	// Slash
	FText SlashText = FText::FromString("/");
	FVector2D SlashSize = FVector2D{10, 20};
	FVector2D SlashPosition = FVector2D{80+8, 0};
	EHorizontalAlignment SlashHAlign = HAlign_Left;
	EVerticalAlignment SlashVAlign = VAlign_Center;

	// Max
	FVector2D MaxSize = FVector2D{50, 20};
	FVector2D MaxPosition = FVector2D{90+8, 0};
	EHorizontalAlignment MaxHAlign = HAlign_Left;
	EVerticalAlignment MaxVAlign = VAlign_Center;

	// Bar
	FLinearColor BarBackgroundColor = FLinearColor::Black;
	float BarPadding = 2;
	FVector2D BarSize = FVector2D{125, 20};
	FVector2D BarPosition = FVector2D{140+8, 0};
	EHorizontalAlignment BarHAlign = HAlign_Left;
	EVerticalAlignment BarVAlign = VAlign_Center;

#pragma endregion

};
