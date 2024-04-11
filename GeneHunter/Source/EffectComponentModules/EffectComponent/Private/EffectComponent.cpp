#include "EffectComponent.h"

bool UEffectComponent::IsComponentTickEnabled() const
{
	return Super::IsComponentTickEnabled();
}

int32 UEffectComponent::GetStacks()
{
	const uint16 OGStacks = Stacks;
	int32 ReturnedStacks = Stacks;
	GetStacksOutlet.ExecuteBefore(OGStacks, ReturnedStacks);
	GetStacksOutlet.ExecuteAfter(OGStacks, ReturnedStacks);
	return ReturnedStacks;
}

void UEffectComponent::SetStacks(const int32 NewStacks)
{
	if (NewStacks <= 0)
	{
		Stacks = 0;
		DestroyComponent();
	} else
	{
		const uint16 CachedStacks = Stacks;
		Stacks = FMath::Clamp(NewStacks, 1, MaxStacks());
		if (Stacks >= CachedStacks)
		{
			OnRefreshStacks();
		}
		if (Stacks < CachedStacks)
		{
			OnReduceStacks();
		}
	}
}

void UEffectComponent::AddStacks(const int32 Amount)
{
	SetStacks(GetStacks() + Amount);
}

void UEffectComponent::RemoveStacks(const int32 Amount)
{
	SetStacks(GetStacks() - Amount);
}

int32 UEffectComponent::MaxStacks()
{
	return 1;
}

void UEffectComponent::OnRefreshStacks()
{
}

void UEffectComponent::OnReduceStacks()
{
}

float UEffectComponent::GetPriority()
{
	return 50;
}

FSupportingText UEffectComponent::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("No dev note"),
		FText::FromString("No description set. Surely this is an oversight."),
		FText::FromString("Flavorless! Disgusting...")
	};
}

FText UEffectComponent::GetDisplayName()
{
	FString ShortName = "__ERROR!__";
	GetFullName().Split(" ", &ShortName, nullptr);
	return FText::FromString(ShortName);
}

bool UEffectComponent::IsPersistent() const
{
	return true;
}

bool UEffectComponent::IsSilenced() const
{
	return bSilenced;
}

void UEffectComponent::Silence()
{
	bSilenced = true;
}

void UEffectComponent::Unsilence()
{
	bSilenced = false;
}

bool UEffectComponent::IsVisibleToUI() const
{
	return false;
}

bool UEffectComponent::IsPurgeable() const
{
	return false;
}

EStackChangeResult UEffectComponent::Purge(const int32 Amount)
{
	EStackChangeResult Result = EStackChangeResult::None;
	if (IsPurgeable())
	{
		Result = EStackChangeResult::Purged;
		const uint16 OldStacks = GetStacks();
		RemoveStacks(Amount);
		if (GetStacks() < OldStacks)
		{
			Result |= EStackChangeResult::StacksReduced;
		}
		if (GetStacks() > OldStacks)
		{
			Result |= EStackChangeResult::StacksIncreased;
		}
	}
	return Result;
}

auto UEffectComponent::OnComponentCreated() -> void
{

	// Delegate
	OnAddEffectOutlet.ExecuteBefore(this);
	
	// Search owner for another component of the same name. If we find one, we don't attach---instead, we just up the
	// stacks.	
	TArray<UActorComponent*> InstanceComponents = GetOwner()->GetInstanceComponents();
	for(UActorComponent* OtherComponent : InstanceComponents)
	{
		UEffectComponent* EffectComponent = dynamic_cast<UEffectComponent*>(OtherComponent);

		// If the Effect had >0 stacks, it must not be new (since the default value is 0). This is how we avoid mixing
		//	up which is the old and which is the new.
		if (EffectComponent && EffectComponent->GetDisplayName().EqualTo(GetDisplayName()) && EffectComponent->GetStacks() > 0)
		{
			EffectComponent->AddStacks(1);
			GetOwner()->RemoveOwnedComponent(this);
			return;
		}
	}

	// Didn't find any w/this name; must be new
	SetStacks(1);
	Added = true;
	
	// Supah
	Super::OnComponentCreated();

	// Delegate
	OnAddEffectOutlet.ExecuteAfter(this);
}

void UEffectComponent::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	if (!bRemoveOutletExecuted)
	{
		OnRemoveEffectOutlet.ExecuteBefore(this);
	}
	Super::OnComponentDestroyed(bDestroyingHierarchy);
	if (!bRemoveOutletExecuted)
	{
		OnRemoveEffectOutlet.ExecuteAfter(this);
	}
	bRemoveOutletExecuted = true;
}

void UEffectComponent::OnUnregister()
{
	if (!bRemoveOutletExecuted)
	{
		OnRemoveEffectOutlet.ExecuteBefore(this);
	}
	Super::OnUnregister();
	if (!bRemoveOutletExecuted)
	{
		OnRemoveEffectOutlet.ExecuteAfter(this);
	}
	bRemoveOutletExecuted = true;
}

bool UEffectComponent::ShouldApplyEffect()
{

	// Check stacks
	if (GetStacks() <= 0)
	{
		// Could be a miscommunication, so let's do this. This should destroy this component, too
		SetStacks(0);
		return false;
	}

	// Check silence state
	return !IsSilenced();
	
}
