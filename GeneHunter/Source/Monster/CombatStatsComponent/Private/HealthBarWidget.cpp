// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

#include "Components/WidgetComponent.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Set up the delegate
	AfterModifyStat.Delegate.Clear();
	AfterModifyStat.Priority = UEffectableComponent::UIPriority;
	AfterModifyStat.Delegate.BindDynamic(this, &UHealthBarWidget::UpdateHealthCall);

	// Check for stats component already attached
	if (const UWidgetComponent* WidgetComponent = GetTypedOuter<UWidgetComponent>())
	{
		if (const AActor* OwningActor = WidgetComponent->GetOwner())
		{
			StatsComponent = OwningActor->FindComponentByClass<UCombatStatsComponent>();

			if (StatsComponent)
			{
			
				// This way we don't have to check against null anymore
				bStatsIsValid = true;
		
				// Add to outlet array
				StatsComponent->ModifyStatOutlet.AddAfter(AfterModifyStat);

				// Fire event first time
				UpdateHealth();
			
			} else
			{
				UE_LOG(LogTemp, Warning, TEXT("No CombatStats found! This is required for a HealthBarWidget."))
				bStatsIsValid = false;
			}
		}
	} else
	{
		UE_LOG(LogTemp, Warning, TEXT("%s should be implemented with a %s!"),
			*UHealthBarWidget::StaticClass()->GetName(),
			*UWidgetComponent::StaticClass()->GetName()
			)
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
	const bool bChangedStats = StatsComponent != NewCombatStats;
	
	// Assign 
	StatsComponent = NewCombatStats;
	
	// New?
	if (bChangedStats && bStatsIsValid)
	{
		UpdateHealth();
	}
}

void UHealthBarWidget::UpdateHealth_Implementation()
{
}

void UHealthBarWidget::UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType,
                                        const EModificationMode Mode, const float OGValue, const float NewValue)
{
	if (Stat == EStatEnum::Health)
	{
		if (bStatsIsValid)
		{

			// Ensure bound
			if (!AfterModifyStat.Delegate.IsBound())
			{
				AfterModifyStat.Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UHealthBarWidget, UpdateHealthCall));
			}

			// Execute main call
			UpdateHealth();
		} else
		{
			UE_LOG(LogTemp, Error, TEXT("CombatStats is required on HealthBarWidget! Do so via SetCombatStats in the Blueprint."))
		}
	}
}
