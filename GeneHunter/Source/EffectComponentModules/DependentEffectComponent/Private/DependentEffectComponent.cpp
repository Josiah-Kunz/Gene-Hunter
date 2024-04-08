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
	bHasOwner = Owner != nullptr;
	if (bHasOwner)
	{
		ApplyEffect();
	}
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
	if (bHasOwner)
	{
		return Owner->GetPriority();
	}
	return 0;
}

int32 UDependentEffectComponent::GetStacks()
{
	if (bHasOwner)
	{
		return Owner->GetStacks();
	}
	return 0;
}

int32 UDependentEffectComponent::MaxStacks()
{
	if (bHasOwner)
	{
		return Owner->MaxStacks();
	}
	return 0;
}

bool UDependentEffectComponent::ShouldApplyEffect()
{
	if (bHasOwner)
	{
		return Owner->ShouldApplyEffect();
	}
	return false;
}

bool UDependentEffectComponent::IsVisibleToUI() const
{
	return false;
}
