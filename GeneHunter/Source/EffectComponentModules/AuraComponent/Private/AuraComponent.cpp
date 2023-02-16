#include "AuraComponent.h"

bool UAuraComponent::IsPurgeable() const
{
	return false;
}

bool UAuraComponent::IsVisibleToUI() const
{
	return true;
}
