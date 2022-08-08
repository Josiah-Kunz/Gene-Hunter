#pragma once
#include "TextWidgetParameters.h"

struct FBarWidgetParameters : public FTextWidgetParameters
{
public:
	
	FLinearColor BackgroundColor;
	FLinearColor BarColor;
	float BarFraction;
	float Padding = 2;

};
