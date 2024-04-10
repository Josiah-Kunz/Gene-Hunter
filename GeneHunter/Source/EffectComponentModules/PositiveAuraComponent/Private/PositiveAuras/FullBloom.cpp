#include "FullBloom.h"

#include "ComponentUtilities.h"

UFullBloom::UFullBloom()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FSupportingText UFullBloom::GetSupportingText()
{
	return FSupportingText{
		FText::FromString(""),
		PermStatMod->GetDescriptionText(),
		FText::FromString("Blooooooom!")
	};
}

void UFullBloom::OnComponentCreated()
{
	Super::OnComponentCreated();
	ADD_COMPONENT(UPermStatMod, PermStatMod, GetOwner())
	PermStatMod->StatMods = {
		{EStatEnum::Health, HealthIncrease, EModificationMode::AddPercentage, EStatValueType::Permanent}
	};
	PermStatMod->SetOwner(this);
}

void UFullBloom::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	PermStatMod->DestroyComponent();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

void UFullBloom::OnUnregister()
{
	PermStatMod->DestroyComponent();
	Super::OnUnregister();
}

float UFullBloom::GetHPIncrease() const
{
	return HealthIncrease;
}
