#include "DependentEffectComponent.h"

void UDependentEffectComponent::SetOwner(UEffectComponent* NewOwner)
{

	// Remove from previous
	if (Owner != nullptr)
	{
		RemoveEffect();
	}

	// Add new
	Owner = NewOwner;
	ApplyEffect();
}

void UDependentEffectComponent::ApplyEffect()
{
}

void UDependentEffectComponent::RemoveEffect()
{
}

void UDependentEffectComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	RemoveEffect();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UDependentEffectComponent::OnRefreshStacks()
{
	Super::OnRefreshStacks();
	ApplyEffect();
}

void UDependentEffectComponent::OnReduceStacks()
{
	Super::OnReduceStacks();
	if (GetStacks() > 0)
	{
		ApplyEffect();
	} else
	{
		RemoveEffect();
	}
}

void UDependentEffectComponent::Silence()
{
	Super::Silence();
	RemoveEffect();
}

void UDependentEffectComponent::Unsilence()
{
	Super::Unsilence();
	ApplyEffect();
}

float UDependentEffectComponent::GetPriority()
{
	return Owner->GetPriority();
}

int32 UDependentEffectComponent::GetStacks()
{
	return Owner->GetStacks();
}

int32 UDependentEffectComponent::MaxStacks()
{
	return Owner->MaxStacks();
}

bool UDependentEffectComponent::ShouldApplyEffect()
{
	return Owner->ShouldApplyEffect();
}

bool UDependentEffectComponent::IsVisibleToUI() const
{
	return false;
}
