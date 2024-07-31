// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Set up the delegate
	AfterModifyStat.Delegate.Clear();
	AfterModifyStat.Priority = UEffectableComponent::UIPriority;
	AfterModifyStat.Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UHealthBarWidget, UpdateHealthCall));
}

UCombatStatsComponent* UHealthBarWidget::GetCombatStats_Implementation()
{
	return StatsComponent;
}

void UHealthBarWidget::SetCombatStats_Implementation(UCombatStatsComponent* NewCombatStats)
{

	// Don't wanna set garbage
	if (NewCombatStats == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("StatsComponent required on HealthBarWidget!"))
	} else
	{

		// Set it
		StatsComponent = NewCombatStats;
		bStatsIsValid = true;
		
		// Add to outlet array
		StatsComponent->ModifyStatOutlet.AddAfter(AfterModifyStat);

		// Fire event first time
		UpdateHealth();
		UE_LOG(LogTemp, Warning, TEXT("StatsComponent were set successfully!"))
	}
}

void UHealthBarWidget::UpdateHealth_Implementation()
{
}

void UHealthBarWidget::UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType,
                                        const EModificationMode Mode, const float OGValue, float& AttemptedValue)
{
	if (Stat == EStatEnum::Health)
	{
		if (bStatsIsValid)
		{

			// Ensure bound
			if (!AfterModifyStat.Delegate.IsBound())
			{
				UE_LOG(LogTemp, Error, TEXT("Wasn't bound. Rebinding."))
				AfterModifyStat.Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UHealthBarWidget, UpdateHealthCall));
			}
			if (!AfterModifyStat.Delegate.IsBound())
			{
				UE_LOG(LogTemp, Error, TEXT("Still not bound. WTF?"))
			}

			// Execute main call
			UpdateHealth();
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatStats is required on HealthBarWidget! Do so via SetCombatStats in the Blueprint."))
		}
	}
}
