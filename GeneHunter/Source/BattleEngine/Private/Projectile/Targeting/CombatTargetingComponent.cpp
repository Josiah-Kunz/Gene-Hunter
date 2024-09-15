#include "CombatTargetingComponent.h"

UCombatTargetingComponent::UCombatTargetingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

FVector UCombatTargetingComponent::GetAttackVector()
{
	return FVector{0, 0, 0};
}

UCombatStatsComponent* UCombatTargetingComponent::GetTarget()
{
	return nullptr;
}

