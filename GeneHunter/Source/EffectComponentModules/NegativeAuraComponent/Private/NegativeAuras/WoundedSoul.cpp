#include "WoundedSoul.h"
#include "ComponentUtilities.h"

#include "StatValueType.h"
#include "StatEnum.h"
#include "ModificationMode.h"

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

	// Is it harmful? If so, that's no healing!
	const bool bIsHarmful = StatsComponent->GetModifiedValue(TargetStat, AttemptedValue, ValueType, Mode) < OriginalValue;
	if (bIsHarmful)
	{
		return;
	}

	// Reduce accordingly
	AttemptedValue *= (100-HealingReduction)/100;
	
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
	//StatsComponent->ModifyStatOutlet.RemoveBefore(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UWoundedSoul::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("Effects like this is the only way healing isn't OP. You know, there's some counterplay."),
		 FText::FromString(FString::Printf(TEXT("%s%% healing"), *FString::SanitizeFloat(HealingReduction))),
		FText::FromString("Time won't heal this wound.")
	};
	
}
