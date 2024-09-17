#include "ProjectileDirectionTarget.h"

#include "ComponentUtilities.h"

void UProjectileDirectionTarget::InitializeProjectile(AActor* MoveCaster)
{
	Super::InitializeProjectile(MoveCaster);
	AssignTargetingComponent();
}

FVector UProjectileDirectionTarget::GetDirection()
{

	const FVector DefaultVector = FVector::ZeroVector;
	
	// Guard no caster
	if (!Caster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s [%s] has no Caster! Make sure to assign one on initialization."),
				*UProjectileDirectionTarget::StaticClass()->GetName(),
				*this->GetPathName()
				);
		return DefaultVector;
	}

	// Guard TargetingComponent
	if (!TargetingComponent)
	{
		AssignTargetingComponent();
		if (!TargetingComponent)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s [%s] is missing [%s]! Make sure you add one to its owner %s."),
					*UProjectileDirectionTarget::StaticClass()->GetName(),
					*this->GetPathName(), 
					*UCombatTargetingComponent::StaticClass()->GetName(),
					*Caster->GetPathName()
					);
			return DefaultVector;
		}
	}

	// Do we actually have a target?
	const UCombatStatsComponent* TargetStats = TargetingComponent->GetTarget();
	if (!TargetStats)
	{
		return DefaultVector;
	}

	// Get vector from caster to target
	return TargetStats->GetOwner()->GetActorLocation() - Projectile->GetOwner()->GetActorLocation();
	
}

void UProjectileDirectionTarget::AssignTargetingComponent()
{
	SEARCH_FOR_COMPONENT(UCombatTargetingComponent, TargetingComponent, Caster)
}
