#include "DependentEffectComponent.h"

void UDependentEffectComponent::CallRemoveEffect(const UEffectComponent* EffectToRemove)
{
	RemoveEffect();
}

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
	BIND_DELEGATE(OnRemoveDelegate, UDependentEffectComponent::CallRemoveEffect);
	Owner->OnRemoveEffectOutlet.AddBefore(OnRemoveDelegate);
}

void UDependentEffectComponent::RemoveEffect()
{
	// Do we need to unbind here? No---we own the delegate and the function!
	// The Delegate will only get added to/removed from Owners' arrays.

	// We also don't need this:
	//	Owner->OnRemoveEffectOutlet.RemoveBefore(OnRemoveDelegate);
	// It is invoked while OnRemoveEffectOutlet is looping over its delegates. If we remove it, the TArray collection
	// will complain that it has been changed. And we're only ever invoking it whenever the main effect (Owner) is
	// being destroyed.
	
	DestroyComponent();
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
		return Owner->ShouldApplyEffect() && !bDeactivated;
	}
	return false;
}

bool UDependentEffectComponent::IsVisibleToUI() const
{
	return false;
}
