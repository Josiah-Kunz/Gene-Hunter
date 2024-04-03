#include "WoundedSoul.h"
#include "ComponentUtilities.h"

UWoundedSoul::UWoundedSoul()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UWoundedSoul::BeforeModifyStats(const EStatEnum TargetStat, const EStatValueType ValueType,
	const EModificationMode Mode, const float OriginalValue, float& AttemptedValue)
{
	// If silenced, do nothing
	if (IsSilenced())
	{
		return;
	}

	// If not current health, do nothing
	if (TargetStat != EStatEnum::Health || ValueType != EStatValueType::Current)
	{
		return;
	}

	// Find the healing. If it's negative, (in the inflection of "that's no moon!") that's no healing!
	const float Healing = AttemptedValue - OriginalValue;
	if (Healing <= 0)
	{
		return;
	}

	// Reduce accordingly
	AttemptedValue = OriginalValue + (100-HealingReduction)/100 * Healing;
	
}

void UWoundedSoul::OnComponentCreated()
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
	BIND_DELEGATE(Delegate, UWoundedSoul::BeforeModifyStats);
	StatsComponent->ModifyStatOutlet.AddBefore(Delegate);
	
}

void UWoundedSoul::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	StatsComponent->ModifyStatOutlet.RemoveBefore(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UWoundedSoul::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("Effects like this is the only way healing isn't OP. You know, there's some counterplay."),
		 FText::FromString(FString::Printf(TEXT("%s%% healing"), *FString::SanitizeFloat(HealingReduction))),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
	
}
