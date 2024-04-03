#include "HoTComponent.h"

#include "ComponentUtilities.h"

EModificationMode UHoTComponent::Mode()
{
	return EModificationMode::AddPercentage;
}

float UHoTComponent::HPS()
{
	return 1;
}

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
	Super::DoEffect();
	StatsComponent->ModifyStat(EStatEnum::Health, HPS() * TickDuration() * GetStacks(), EStatValueType::Current,
				Mode());
}
