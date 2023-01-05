#include "EffectComponent.h"

bool UEffectComponent::IsComponentTickEnabled() const
{
	return Super::IsComponentTickEnabled();
}

int UEffectComponent::GetStacks()
{
	return Stacks;
}

void UEffectComponent::SetStacks(const int NewStacks)
{
	if (NewStacks <= 0)
	{
		Stacks = 0;
		//DestroyComponent(); // TODO
	} else
	{
		const int CachedStacks = Stacks;
		Stacks = FMath::Clamp(NewStacks, 1, MaxStacks());
		if (Stacks >= CachedStacks)
			OnRefreshStacks();
	}
}

int UEffectComponent::MaxStacks()
{
	return 1;
}

void UEffectComponent::OnRefreshStacks()
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

FText UEffectComponent::GetName()
{
	FString ShortName = "__ERROR!__";
	GetFullName().Split(" ", &ShortName, nullptr);
	return FText::FromString(ShortName);
}

auto UEffectComponent::OnComponentCreated() -> void
{
	SetStacks(1);
	Super::OnComponentCreated();
	
}
