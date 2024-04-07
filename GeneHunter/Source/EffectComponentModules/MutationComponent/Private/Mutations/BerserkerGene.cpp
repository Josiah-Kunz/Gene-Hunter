#include "BerserkerGene.h"
#include "ComponentUtilities.h"
#include "PermStatMod.h"

UBerserkerGene::UBerserkerGene()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBerserkerGene::OnComponentCreated()
{

	Super::OnComponentCreated();
	ADD_COMPONENT(UPermStatMod, PermStatMod, GetOwner())
	PermStatMod->StatMods = {
		{EStatEnum::PhysicalAttack, 15, EModificationMode::AddPercentage, EStatValueType::Permanent},
		{EStatEnum::PhysicalDefense, -10, EModificationMode::AddPercentage, EStatValueType::Permanent},
		{EStatEnum::SpecialDefense, -10, EModificationMode::AddPercentage, EStatValueType::Permanent},
	};
	PermStatMod->StatsComponent->RecalculateStats();
}

FSupportingText UBerserkerGene::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("I'm not entirely sure if berserkers should lose defense, gain speed, or have +PhA & +SpA. I was just so mad that the final item in Pokemon Silver was this item that was unique and consumable. I never used it!"),
		PermStatMod->GetDescriptionText(),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
}
