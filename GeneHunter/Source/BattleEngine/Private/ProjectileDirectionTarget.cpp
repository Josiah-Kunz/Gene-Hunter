#include "ProjectileDirectionTarget.h"

FVector UProjectileDirectionTarget::GetDirection()
{
	const FVector TargetLoc = Target->GetActorLocation();
	const FVector ThisLoc = GetOwner()->GetActorLocation();
	return TargetLoc - ThisLoc;
}

