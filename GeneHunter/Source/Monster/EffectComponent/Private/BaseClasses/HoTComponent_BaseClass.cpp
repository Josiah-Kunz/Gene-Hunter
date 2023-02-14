#include "HoTComponent_BaseClass.h"

#include "ComponentUtilities.h"


float UHoTComponent_BaseClass::GetAmount()
{
	return StatsComponent->GetStat(EStatEnum::Health).GetPermanentValue() * 0.01f * GetStacks();
}

float UHoTComponent_BaseClass::GetTickRate()
{
	return 1;
}

void UHoTComponent_BaseClass::OnComponentCreated()
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

void UHoTComponent_BaseClass::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
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
