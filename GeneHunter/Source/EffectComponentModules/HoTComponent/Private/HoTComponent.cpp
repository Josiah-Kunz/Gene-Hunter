#include "HoTComponent.h"

#include "ComponentUtilities.h"

EModificationMode UHoTComponent::Mode()
{
	return EModificationMode::AddPercentage;
}

EStatReferenceType UHoTComponent::StatReferenceType()
{
	return EStatReferenceType::Permanent;
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
	{
		UE_LOG(LogTemp, Warning, TEXT("No UStatsComponent found!"
			" This is required for HoTComponent."))
		DestroyComponent();
		
		return;
	}

	// Must still be alive
	Super::OnComponentCreated();
}

void UHoTComponent::DoEffect()
{
	Super::DoEffect();
	StatsComponent->ModifyStat(EStatEnum::Health, HPS() * TickDuration() * GetStacks(),
		EStatValueType::Current, Mode(), StatReferenceType());
}
