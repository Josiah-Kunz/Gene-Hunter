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

float UFullBloom::GetHPIncrease() const
{
	return HealthIncrease;
}
