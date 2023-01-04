#include "EffectComponent.h"

/*
template <typename T>
T* UEffectComponent::ApplyEffect(AActor* Owner)
{

	// Search owner for another component of the same name. If we find one, we don't attach---instead, we just up the
	// stacks.
	T* ExistingEffect = Owner->FindComponentByClass<T>();
	if (IsValid(ExistingEffect))
	{
		ExistingEffect->SetStacks(ExistingEffect->GetStacks()+1);
		return ExistingEffect;
	}

	// None exist---let's add a new one
	T* Effect = NewObject<T>(Owner);
	if (Effect)
	{
		Owner->AddInstanceComponent(Effect);  
		Effect->RegisterComponent();
	}
	return Effect;
}

template <typename T>
T UEffectComponent::AddEffect(AActor* Owner)
{
	return ApplyEffect<T>(Owner);
}
*/

void UEffectComponent::AddEffect(TSubclassOf<UEffectComponent> EffectClass, AActor* Owner)
{
	// Search owner for another component of the same name. If we find one, we don't attach---instead, we just up the
	// stacks.
	//UEffectComponent ExistingEffect = Owner->FindComponentByClass(EffectClass);
	UActorComponent* ActorComponent = Owner->FindComponentByClass(EffectClass);
	if (IsValid(ActorComponent))
	{
		UEffectComponent* ExistingEffect = dynamic_cast<UEffectComponent*>(ActorComponent);
		ExistingEffect->SetStacks(ExistingEffect->GetStacks()+1);
		return;
	}

	// None exist---let's add a new one
	UActorComponent* Component = Owner->AddComponentByClass(EffectClass, false, FTransform::Identity, false);
	Component->RegisterComponent();
}

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
