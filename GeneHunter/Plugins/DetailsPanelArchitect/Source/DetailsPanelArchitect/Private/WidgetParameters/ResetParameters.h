#pragma once

struct FResetParameters
{

public:

	bool bShowReset = false;
	TFunction<void()> OnReset = [](){};
	FText Tooltip = FText::FromString("Reset this property to its default value.");
	
};