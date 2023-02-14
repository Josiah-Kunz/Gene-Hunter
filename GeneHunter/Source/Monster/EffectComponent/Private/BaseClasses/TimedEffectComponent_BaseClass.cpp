#include "TimedEffectComponent_BaseClass.h"

UTimedEffectComponent_BaseClass::UTimedEffectComponent_BaseClass()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UTimedEffectComponent_BaseClass::StartingDuration()
{
	return 1;
}

void UTimedEffectComponent_BaseClass::OnComponentCreated()
{
	
	Super::OnComponentCreated();

	// Didn't fine one---simply attach
	RemainingTime = StartingDuration();
}

void UTimedEffectComponent_BaseClass::TickComponent(const float DeltaTime, const ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	RemainingTime -= DeltaTime;

	if (RemainingTime < 0)
		DestroyComponent();
}


