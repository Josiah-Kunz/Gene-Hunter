#include "EternalPhoenix.h"

#include "ComponentUtilities.h"

FSupportingText UEternalPhoenix::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("Please only use this for non-Monsters, such as the training dummy."),
		 FText::FromString(FString::Printf(TEXT("When killed, heal to full."))),
		 FText::FromString("Impossible to balance. More like Eternal Problem!")
	};
}

void UEternalPhoenix::OnComponentCreated()
{
	
	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No %s found!"
			" This is required for %s."),
			*UCombatStatsComponent::StaticClass()->GetName(),
			*UEternalPhoenix::StaticClass()->GetName()
			)
		DestroyComponent();
		return;
	}
	
	// Trigger when applied for the first time
	Super::OnComponentCreated();
	
}

void UEternalPhoenix::ApplyEffect()
{

	// Call super and see if we should return
	Super::ApplyEffect();
	if (!ShouldApplyEffect())
	{
		return;
	}

	// Bind the delegate
	BIND_DELEGATE(ModifyStatOutlet, UEternalPhoenix::HealToFull);
	StatsComponent->ModifyStatOutlet.AddBefore(ModifyStatOutlet);
}

void UEternalPhoenix::RemoveEffect()
{
	Super::RemoveEffect();
	StatsComponent->ModifyStatOutlet.RemoveBefore(ModifyStatOutlet);
}

float UEternalPhoenix::GetPriority()
{
	return 500;
}

/* No, don't make this const---BIND_DELEGATE needs it to match exactly. */
void UEternalPhoenix::HealToFull(const EStatEnum TargetStat, const EStatValueType ValueType,
	const EModificationMode Mode, const float OriginalValue, float& AttemptedValue)
{

	// Are we modifying current health?
	if (!(TargetStat == EStatEnum::Health && ValueType == EStatValueType::Current))
	{
		return;
	}
	
	// Are we about to die?
	const float CurrentHealth = StatsComponent->GetStatValue(TargetStat, ValueType);
	FCombatStat HealthStat = StatsComponent->GetStat(TargetStat);
	const float FutureHealth = HealthStat.GetModification(CurrentHealth, Mode, AttemptedValue);
	if (FutureHealth > 0)
	{
		return;
	}
	
	// Set the attempted value to heal to full
	const float FullHealth = StatsComponent->GetStatValue(TargetStat, EStatValueType::Permanent);
	switch(Mode)
	{
	case EModificationMode::AddAbsolute: case EModificationMode::SetDirectly:
		
		AttemptedValue = FullHealth;
		break;
	case EModificationMode::AddFraction:
		AttemptedValue = 1;
		break;
	case EModificationMode::AddPercentage:
		AttemptedValue = 100;
		break;
	case EModificationMode::MultiplyAbsolute:
		if (CurrentHealth > 0)
		{
			AttemptedValue = FullHealth/CurrentHealth;
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("Error in [%s]! Trying to revive [%s]'s [%s], but its health is somehow already zero. How did that happen?!"),
					*UEternalPhoenix::StaticClass()->GetName(),
					*StatsComponent->GetOwner()->GetName(),
					*StatsComponent->GetName()
				)
			UE_LOG(LogTemp, Error, TEXT("Owner's full path: [%s]"),
					*StatsComponent->GetOwner()->GetPathName()
				)
		}
		break;
	case EModificationMode::MultiplyPercentage:
		const float CurrentPercent = CurrentHealth/FullHealth * 100;
		if (CurrentPercent > 0)
		{
			AttemptedValue = 100/CurrentPercent;
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("Error in [%s]! Trying to revive [%s]'s [%s], but its health is somehow already zero. How did that happen?!"),
					*UEternalPhoenix::StaticClass()->GetName(),
					*StatsComponent->GetOwner()->GetName(),
					*StatsComponent->GetName()
				)
			UE_LOG(LogTemp, Error, TEXT("Owner's full path: [%s]"),
					*StatsComponent->GetOwner()->GetPathName()
				)
		}
		break;
	}
}
