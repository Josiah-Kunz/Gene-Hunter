// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

void UHealthBarWidget::InitializeStats(){

	// Set up the delegate regardless of StatsComponent
	if (!bStatsInitialized){
		AfterModifyStat.Delegate.Clear();
		AfterModifyStat.Priority = UEffectableComponent::UIPriority;
		AfterModifyStat.Delegate.BindDynamic(this, &UHealthBarWidget::UpdateHealthCall);

		// Flag
		bStatsInitialized = true;
	}

	// Careful!
	if (StatsComponent)
	{
			
		// This way we don't have to check against null anymore
		bStatsIsValid = true;
		
		// Add to outlet array
		StatsComponent->ModifyStatOutlet.AddAfter(AfterModifyStat);

		// Fire event first time
		UpdateHealth();
			
	}
}

UCombatStatsComponent* UHealthBarWidget::GetCombatStats_Implementation()
{
	return StatsComponent;
}

void UHealthBarWidget::SetCombatStats_Implementation(UCombatStatsComponent* NewCombatStats)
{
	
	// Set bools
	bStatsIsValid = NewCombatStats != nullptr;
	
	// Assign 
	StatsComponent = NewCombatStats;

	// Make sure this stats's health is the one being tracked
	InitializeStats();
}

void UHealthBarWidget::UpdateHealth_Implementation()
{
}

void UHealthBarWidget::UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType,
                                        const EModificationMode Mode, const float OGValue, const float NewValue)
{

	// Need to init?
	if (!bStatsInitialized)
	{
		InitializeStats();
	}
	
	if (Stat == EStatEnum::Health)
	{
		if (bStatsIsValid)	// No, don't combine booleans---we have a very specific error message
		{
			UpdateHealth();
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatStats is required on HealthBarWidget! Do so via SetCombatStats in the Blueprint."))
		}
	}
}
