#pragma once
#include "TextWidgetParameters.h"


struct FEditableTextBoxWidgetParameters : FTextWidgetParameters
{
public:

	TFunction<void (const FText&, ETextCommit::Type&)> OnTextCommitted;


};
