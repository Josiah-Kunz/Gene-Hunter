// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
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
		
		// Set up the delegate
		AfterModifyStat.Delegate.Clear();
		AfterModifyStat.Priority = UEffectableComponent::UIPriority;
		AfterModifyStat.Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UHealthBarWidget, UpdateHealthCall));
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
			UpdateHealth();
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatStats is required on HealthBarWidget! Do so via SetCombatStats in the Blueprint."))
		}
	}
}
