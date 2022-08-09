#pragma once
#include "TextWidgetParameters.h"

struct FBarWidgetParameters : public FTextWidgetParameters
{
public:
	
	FLinearColor BarColor;
	float BarFraction;
	FLinearColor BackgroundColor = FLinearColor::Black;
	float Padding = 2;

};
