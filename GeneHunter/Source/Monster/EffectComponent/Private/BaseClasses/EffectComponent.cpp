#include "EffectComponent.h"

#include "ComponentUtilities.h"
#include "BPLibraries/Public/UtilityFunctionLibrary.h"

int UEffectComponent::GetStacks()
{
	return Stacks;
}

void UEffectComponent::SetStacks(const int NewStacks)
{
	Stacks = FMath::Clamp(NewStacks, 1, MaxStacks());
}

int UEffectComponent::MaxStacks()
{
	return 1;
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
	FString Name = typeid(this).name();
	Name.RemoveAt(0);	// Removes the "U"
	Name = UUtilityFunctionLibrary::SplitCamelCase(Name);
	return FText::FromString(Name);
}

void UEffectComponent::OnComponentCreated()
{
	Super::OnComponentCreated();

	// Find the StatsComponent and assign it
	REQUIRE_COMPONENT(UStatsComponent, StatsComponent, GetOwner())
}
