#include "EffectComponent.h"

float UEffectComponent::GetPriority()
{
	return 50;
}

FSupportingText UEffectComponent::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("No dev note"),
		FText::FromString("No description set. Surely this is an oversight."),
		FText::FromString("Flavorless!")
	};
}
