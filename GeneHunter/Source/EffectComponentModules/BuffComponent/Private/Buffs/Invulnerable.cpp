#include "Invulnerable.h"

#include "ComponentUtilities.h"

void UInvulnerable::InitializeEffect()
{

	// Assign stats
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, Stats, GetOwner(), true);

	// Super it
	Super::InitializeEffect();

	// Bind
	BIND_DELEGATE(Delegate, UInvulnerable::DontTakeDamage)

	// Add it
	Stats->ModifyStatOutlet.AddBefore(Delegate);
}

void UInvulnerable::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Stats->ModifyStatOutlet.RemoveBefore(Delegate);
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UInvulnerable::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("All timed invulnerabilities should inherit from this and change Priority/duration/other things."),
		FText::FromString("Unable to take damage."),
		FText::FromString("\"They are not a god; you can have your revenge soon.\"")
	};
}

float UInvulnerable::StartingDuration()
{
	return 1;
}

float UInvulnerable::GetPriority()
{
	return 100;
}

void UInvulnerable::DontTakeDamage(const EStatEnum TargetStat, const EStatValueType ValueType,
                                   const EModificationMode Mode, const float OriginalValue, float& AttemptedValue)
{
	if (ShouldApplyEffect())
	{
		const bool bIsHP = TargetStat == EStatEnum::Health &&
			(ValueType == EStatValueType::Current || ValueType == EStatValueType::Permanent);
		if (bIsHP)
		{
			const bool bIsHarmful = Stats->IsHarmful(TargetStat, AttemptedValue, ValueType, Mode);
			if (bIsHarmful)
			{
				Stats->AvertReduction(TargetStat, AttemptedValue, ValueType, Mode);
			}
		}
	}
}
