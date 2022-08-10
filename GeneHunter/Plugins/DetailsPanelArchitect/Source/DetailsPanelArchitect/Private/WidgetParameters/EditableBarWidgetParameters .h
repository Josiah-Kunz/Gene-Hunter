#pragma once
#include "BarWidgetParameters.h"
#include "EditableTextBoxWidgetParameters.h"
#include "ResetParameters.h"
#include "TextWidgetParameters.h"

struct FEditableBarWidgetParameters
{
public:

	FTextWidgetParameters Label = {
		FText::GetEmpty(), FText::GetEmpty(),
		FVector2D{30, 20}
	};

	FEditableTextBoxWidgetParameters TextBox = {
		FText::GetEmpty(), FText::GetEmpty(),
		FVector2D{50+8, 20}, FVector2D{30, 0}
	};

	FTextWidgetParameters Slash = {
		FText::FromString("/"), FText::GetEmpty(),
		FVector2D{10, 20},
		FVector2D{80+8, 0}
	};

	FTextWidgetParameters Max = {
		FText::GetEmpty(), FText::GetEmpty(),
		FVector2D{50, 20}, FVector2D{90+8, 0}
	};

	FBarWidgetParameters Bar = {
		{
			FText::GetEmpty(), FText::GetEmpty(),
			FVector2D{125, 20}, FVector2D{140+8, 0}
		},
		FLinearColor::White, 1, FLinearColor::Black, 2
	};

	FResetParameters Reset = {};

};
