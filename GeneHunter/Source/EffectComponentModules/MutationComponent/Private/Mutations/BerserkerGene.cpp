#include "BerserkerGene.h"
#include "ComponentUtilities.h"

UBerserkerGene::UBerserkerGene()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBerserkerGene::AfterRecalculateStats(const EStatEnum InStat, const bool bResetCurrent, const float OriginalCurrent,
		const float OriginalPermanent)
{
	// If silenced, do nothing
	if (IsSilenced())
	{
		return;
	}

	// Do increases + decreases
	ModifyStat(InStat, bResetCurrent, 1);
}

void UBerserkerGene::ModifyStat(const EStatEnum InStat, const bool bResetCurrent, const int8 Scale) const
{
	switch(InStat)
	{
	case EStatEnum::PhysicalAttack:
		StatsComponent->ModifyStat(InStat, PhAIncrease * Scale, EStatValueType::Permanent, EModificationMode::AddPercentage);
		if (bResetCurrent)
		{
			StatsComponent->ModifyStat(InStat, PhAIncrease * Scale, EStatValueType::Current, EModificationMode::AddPercentage);
		}
		break;
	case EStatEnum::PhysicalDefense: case EStatEnum::SpecialDefense:
		StatsComponent->ModifyStat(InStat, -DefDecrease * Scale, EStatValueType::Permanent, EModificationMode::AddPercentage);
		if (bResetCurrent)
		{
			StatsComponent->ModifyStat(InStat, -DefDecrease * Scale, EStatValueType::Current, EModificationMode::AddPercentage);
		}
		break;
	default:
		break;
	}
}

void UBerserkerGene::OnComponentCreated()
{

	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
	{
		return;
	}

	// Must still be alive
	Super::OnComponentCreated();
	
	// Add to delegate array
	Delegate.Delegate.BindDynamic(this, &UBerserkerGene::AfterRecalculateStats);
	StatsComponent->RecalculateStatsOutlet.AddAfter(Delegate);

	// Trigger it to run when attached for the first time (e.g., on Mutation reroll)
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		ModifyStat(Stat, true, 1);
	}
}

void UBerserkerGene::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	StatsComponent->RecalculateStatsOutlet.RemoveAfter(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UBerserkerGene::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("I'm not entirely sure if berserkers should lose defense, gain speed, or have +PhA & +SpA. I was just so mad that the final item in Pokemon Silver was this item that was unique and consumable. I never used it!"),
		FText::FromString("+15% PhA | -10% PhD | -10% SpD"),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
}

void UBerserkerGene::Silence()
{
	Super::Silence();
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		ModifyStat(Stat, true, -1);
	}
}

void UBerserkerGene::Unsilence()
{
	Super::Unsilence();
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		ModifyStat(Stat, true, -1);
	}
}
