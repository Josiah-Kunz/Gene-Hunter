#include "EffectComponent.h"

bool UEffectComponent::IsComponentTickEnabled() const
{
	return Super::IsComponentTickEnabled();
}

int32 UEffectComponent::GetStacks() const
{
	return Stacks;
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

bool UEffectComponent::IsSilenced() const
{
	return Silenced;
}

bool UEffectComponent::IsVisibleToUI() const
{
	return false;
}

bool UEffectComponent::IsPurgeable() const
{
	return false;
}

auto UEffectComponent::OnComponentCreated() -> void
{
	
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
			EffectComponent->SetStacks(EffectComponent->GetStacks()+1);
			GetOwner()->RemoveOwnedComponent(this);
			return;
		}
	}

	// Didn't find any w/this name; must be new
	SetStacks(1);
	Super::OnComponentCreated();
}
