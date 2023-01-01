#include "TimedEffectComponent.h"

UTimedEffectComponent::UTimedEffectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
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


