#pragma once
#include "TextWidgetParameters.h"

struct FBarWidgetParameters : public FTextWidgetParameters
{
public:
	
	FLinearColor BarColor;
	float BarFraction;
	FLinearColor BackgroundColor = FLinearColor{0.01f, 0.01f, 0.01f};
	float Padding = 2;
	FVector4 CornerRadius = FVector4{2, 2, 2, 2};
	FLinearColor OutlineColor = FLinearColor::Black;
};
