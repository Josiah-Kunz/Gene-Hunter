


#include "EditableTextPlus.h"

void UEditableTextPlus::SynchronizeProperties() {
	Super::SynchronizeProperties();
	OnSynchronizeProperties();
	Super::SynchronizeProperties();
}

void UEditableTextPlus::SynchronizeProperty(UWidget* Widget)
{
	Widget->SynchronizeProperties();
}
