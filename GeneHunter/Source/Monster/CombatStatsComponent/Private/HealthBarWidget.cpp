// Fill out your copyright notice in the Description page of Project Settings.

#include "HealthBarWidget.h"

void UHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	// Guard
	if (StatsComponent == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("StatsComponent required on HealthBarWidget!"))
	} else
	{
		AfterModifyStat.Delegate.Clear();
		AfterModifyStat.Priority = UEffectableComponent::UIPriority;
		AfterModifyStat.Delegate.BindUFunction(this, GET_FUNCTION_NAME_CHECKED(UHealthBarWidget, UpdateHealthCall));
		StatsComponent->ModifyStatOutlet.AddAfter(AfterModifyStat);
	}
}

void UHealthBarWidget::UpdateHealthCall(const EStatEnum Stat, const EStatValueType ValueType,
	const EModificationMode Mode, const float OGValue, float& AttemptedValue)
{
	UpdateHealth();
}
