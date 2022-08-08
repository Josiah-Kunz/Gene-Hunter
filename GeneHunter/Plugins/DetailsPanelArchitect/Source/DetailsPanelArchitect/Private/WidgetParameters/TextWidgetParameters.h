#pragma once

struct FTextWidgetParameters
{
public:
	FText Text;
	FText Tooltip = FText::GetEmpty();
	FVector2D WidgetSize = FVector2D{30, 20};
	FVector2D WidgetPosition = FVector2D{0, 0};
	EHorizontalAlignment WidgetHAlign = HAlign_Left;
	EVerticalAlignment WidgetVAlign = VAlign_Center;
};