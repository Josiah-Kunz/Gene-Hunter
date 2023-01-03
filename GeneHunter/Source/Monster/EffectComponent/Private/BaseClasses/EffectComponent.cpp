#include "EffectComponent.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"


bool UEffectComponent::IsComponentTickEnabled() const
{
	UE_LOG(LogTemp, Warning, TEXT("HEREEEEE"))
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
	FString ShortName = "";
	GetFullName().Split(" ", &ShortName, nullptr);
	return FText::FromString(
		ShortName
		);
	FString Name = typeid(this).name();
	Name.RemoveAt(0);	// Removes the "U"
	Name = UUtilityFunctionLibrary::SplitCamelCase(Name);
	return FText::FromString(Name);
}

void UEffectComponent::OnComponentCreated()
{
	
	// Search owner for another component of the same name. If we find one, we don't attach---instead, we just up the
	// stacks.	
	TArray<UActorComponent*> InstanceComponents = GetOwner()->GetInstanceComponents();
	UE_LOG(LogTemp, Warning, TEXT("Name is %s"), *(GetName().ToString()) )
	for(UActorComponent* OtherComponent : InstanceComponents)
	{
		UEffectComponent* EffectComponent = dynamic_cast<UEffectComponent*>(OtherComponent);
		if (EffectComponent && EffectComponent->GetName().EqualTo(GetName()))
		{
			EffectComponent->SetStacks(EffectComponent->GetStacks()+1);
			SetStacks(0);
			return;
		}
	}
	
	// Not killed, so must be novel
	SetStacks(1);
	Super::OnComponentCreated();
	
}

void UEffectComponent::OnRegister()
{
	if (IsValid(this))
		Super::OnRegister();
}
