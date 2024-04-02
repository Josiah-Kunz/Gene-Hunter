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

void UTimedEffectComponent::OnRefreshStacks()
{
	Super::OnRefreshStacks();
	if (bStacksRefreshDuration && RemainingTime < StartingDuration())
	{
		RemainingTime = StartingDuration();
		DoEffect();
	}
}

float UTimedEffectComponent::StartingDuration()
{
	return 1;
}

void UTimedEffectComponent::OnComponentCreated()
{
	
	Super::OnComponentCreated();

	// Set mod time. This will also set the first tick.
	RemainingTime = StartingDuration();
	NextModTime = StartingDuration();
}

void UTimedEffectComponent::TickComponent(const float DeltaTime, const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{

	// Keep track of remaining time, 
	RemainingTime -= DeltaTime;

	// If we're destroying this component, don't tick
	if (RemainingTime < 0)
	{
		DestroyComponent();
	} else
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// Check silenced
		if (ShouldApplyEffect())
		{
			
			// Do we need to modify again?
			// Note: while loop prevents losing ticks from system performance. E.g., what if
			// components ticked once every 5 seconds? we'd only tick once with an "if", but still get all of them with a
			// "while".
			while (RemainingTime <= NextModTime)
			{
				NextModTime -= TickDuration;
				DoEffect();
			}
		}
	}
}

void UTimedEffectComponent::DoEffect()
{
}
