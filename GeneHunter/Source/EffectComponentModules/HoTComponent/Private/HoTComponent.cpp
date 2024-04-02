#include "HoTComponent.h"

#include "ComponentUtilities.h"

void UHoTComponent::OnComponentCreated()
{

	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();
}

void UHoTComponent::DoEffect()
{
	StatsComponent->ModifyStat(EStatEnum::Health, HPS * TickDuration * GetStacks(), EStatValueType::Current,
				Mode);
}
