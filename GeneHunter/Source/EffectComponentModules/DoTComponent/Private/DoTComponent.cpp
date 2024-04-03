#include "DoTComponent.h"

#include "ComponentUtilities.h"

EModificationMode UDoTComponent::Mode()
{
	return EModificationMode::AddAbsolute;
}

float UDoTComponent::DPS()
{
	return 1;
}

void UDoTComponent::OnComponentCreated()
{

	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();
	
	Super::OnComponentCreated();
	NextModTime = StartingDuration();
}

void UDoTComponent::DoEffect()
{
	Super::DoEffect();
	StatsComponent->ModifyStat(EStatEnum::Health, -DPS() * TickDuration() * GetStacks(), EStatValueType::Current,
				Mode());
}
