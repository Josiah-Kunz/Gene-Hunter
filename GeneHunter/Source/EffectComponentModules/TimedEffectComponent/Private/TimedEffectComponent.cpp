// Fill out your copyright notice in the Description page of Project Settings.


#include "TimedEffectComponent.h"


// Sets default values for this component's properties
UTimedEffectComponent::UTimedEffectComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

bool UTimedEffectComponent::IsPurgeable() const
{
	return true;
}

bool UTimedEffectComponent::IsVisibleToUI() const
{
	return true;
}

float UTimedEffectComponent::StartingDuration()
{
	return 1;
}

void UTimedEffectComponent::OnComponentCreated()
{
	
	Super::OnComponentCreated();

	// Didn't fine one---simply attach
	RemainingTime = StartingDuration();
}

void UTimedEffectComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RemainingTime -= DeltaTime;

	if (RemainingTime < 0)
		DestroyComponent();
}
