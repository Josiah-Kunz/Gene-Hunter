#include "ProjectileDirectionVector.h"

#include "ComponentUtilities.h"

FVector UProjectileDirectionVector::GetDirection()
{

	// Guard no caster
	if (!Caster)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s [%s] has no Caster! Make sure to assign one on initialization."),
				*UProjectileDirectionVector::StaticClass()->GetName(),
				*this->GetPathName()
				);
		return FVector{0, 0, 0};
	}

	// Get TargetingComponent
	SEARCH_FOR_COMPONENT(UCombatTargetingComponent, TargetingComponent, Caster)
	if (!TargetingComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s [%s] is missing [%s]! Make sure you add one to its owner %s."),
				*UProjectileDirectionVector::StaticClass()->GetName(),
				*this->GetPathName(), 
				*UCombatTargetingComponent::StaticClass()->GetName(),
				*Caster->GetPathName()
				);
		return FVector{0, 0, 0};
	}

	// Return
	return TargetingComponent->GetAttackVector();
}
