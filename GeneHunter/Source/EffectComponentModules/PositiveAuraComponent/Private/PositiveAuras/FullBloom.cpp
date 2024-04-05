#include "FullBloom.h"
#include "ComponentUtilities.h"

#include "StatValueType.h"
#include "StatEnum.h"
#include "ModificationMode.h"

UFullBloom::UFullBloom()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UFullBloom::AfterRecalculateStats(const EStatEnum InStat, const bool bResetCurrent, const float OriginalCurrent,
	const float OriginalPermanent)
{
	StatsComponent->ModifyStat(InStat, HPIncrease, EStatValueType::Permanent,
		EModificationMode::AddPercentage);
	if (bResetCurrent)
	{
		StatsComponent->ModifyStat(InStat, HPIncrease, EStatValueType::Current,
			EModificationMode::AddPercentage);
	}
}

void UFullBloom::OnComponentCreated()
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
	BIND_DELEGATE(Delegate, UFullBloom::BeforeModifyStats);
	StatsComponent->ModifyStatOutlet.AddBefore(Delegate);
	
}

void UFullBloom::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	//StatsComponent->ModifyStatOutlet.RemoveBefore(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UFullBloom::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("Effects like this is the only way healing isn't OP. You know, there's some counterplay."),
		 FText::FromString(FString::Printf(TEXT("%s%% healing"), *FString::SanitizeFloat(HealingReduction))),
		FText::FromString("Time won't heal this wound.")
	};
	
}
