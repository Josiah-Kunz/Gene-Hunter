#include "BrokenSoul.h"

#include "ComponentUtilities.h"

void UBrokenSoul::BeginPlay()
{

	// Assign stats
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, Stats, GetOwner(), true);

	// No stats component?
	if (Stats == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No UStatsComponent found!"
			" This is required for UWoundedSoul."))
		return;
	}
	
	// Super it
	Super::BeginPlay();

	// Bind
	BIND_DELEGATE(Delegate, UBrokenSoul::ReduceHealing)

	// Add it
	Stats->ModifyStatOutlet.AddBefore(Delegate);
}

void UBrokenSoul::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Stats->ModifyStatOutlet.RemoveBefore(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UBrokenSoul::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("A stronger version of WoundedSoul, but probably not the strongest in the game."),
		 FText::FromString(FString::Printf(TEXT("-%s%% healing"), *FString::SanitizeFloat(HealingReduction))),
		FText::FromString("Time *will* heal this wound, but it's gonna cost a lot of therapy money.")
	};
}

float UBrokenSoul::StartingDuration()
{
	return 5;
}

float UBrokenSoul::GetPriority()
{
	return 80;
}

void UBrokenSoul::ReduceHealing(const EStatEnum TargetStat, const EStatValueType ValueType,
                                   const EModificationMode Mode, const float OriginalValue, float& AttemptedValue)
{
	// If silenced, do nothing
	if (!ShouldApplyEffect())
	{
		return;
	}

	// If not current health, do nothing
	if (TargetStat != EStatEnum::Health || ValueType != EStatValueType::Current)
	{
		return;
	}

	// Is it harmful? If so, that's no healing!
	const bool bIsHarmful = Stats->IsHarmful(TargetStat, AttemptedValue, ValueType, Mode);
	if (bIsHarmful)
	{
		return;
	}

	// Reduce accordingly
	AttemptedValue *= (100-HealingReduction)/100;
}
