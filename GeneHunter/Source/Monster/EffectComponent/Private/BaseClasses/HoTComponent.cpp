#include "HoTComponent.h"


float UHoTComponent::GetAmount()
{
	return StatsComponent->Health.GetPermanentValue() * 0.01f * Stacks;
}

float UHoTComponent::GetTickRate()
{
	return 1;
}

void UHoTComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	NextModTime = StartingDuration();
}

void UHoTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Do we need to modify again?
	if (RemainingTime <= NextModTime)
	{
		NextModTime -= GetTickRate();
		StatsComponent->ModifyStat(&StatsComponent->Health, GetAmount(), EStatValueType::Current,
			EModificationMode::AddAbsolute);
	}
}
