#include "DependentEffectComponent.h"

void UDependentEffectComponent::SetOwner(UEffectComponent* NewOwner)
{
	Owner = NewOwner;
}

void UDependentEffectComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

int32 UDependentEffectComponent::GetStacks()
{
	return Super::GetStacks();
}

bool UDependentEffectComponent::IsVisibleToUI() const
{
	return false;
}
