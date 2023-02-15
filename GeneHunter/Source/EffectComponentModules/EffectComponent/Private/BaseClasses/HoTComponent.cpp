#include "HoTComponent.h"

#include "ComponentUtilities.h"


float UHoTComponent::GetAmount()
{
	return StatsComponent->GetStat(EStatEnum::Health).GetPermanentValue() * 0.01f * GetStacks();
}

float UHoTComponent::GetTickRate()
{
	return 1;
}

void UHoTComponent::OnComponentCreated()
{

	// Get StatsComponent
	SEARCH_FOR_COMPONENT(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();
	
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
		StatsComponent->ModifyStat(EStatEnum::Health, GetAmount(), EStatValueType::Current,
			EModificationMode::AddAbsolute);
	}
}
