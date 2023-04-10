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
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();

	// Set mod time
	NextModTime = StartingDuration();
}

void UHoTComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UE_LOG(LogTemp, Warning, TEXT("Ticking!"))
	// Check silenced
	if (ShouldApplyEffect())
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

		// Do we need to modify again?
		// Note: while loop prevents losing ticks from system performance. E.g., what if
		// components ticked once every 5 seconds? we'd only tick once with an "if", but still get all of them with a
		// "while".
		while (RemainingTime <= NextModTime)
		{
			NextModTime -= GetTickRate();
			StatsComponent->ModifyStat(EStatEnum::Health, GetAmount(), EStatValueType::Current,
				EModificationMode::AddAbsolute);
		}
	}
}
