#include "MoveInstance.h"

#include "ProjectileMove.h"

void FMoveInstance::Execute(AActor* Owner)
{

	// Spawn some Actors
	TArray<AActor*> SpawnedObjects = UActorSpawnScheme::SpawnActors(Owner, MoveData->SpawnOnCast);

	// See if there's any projectiles to initialize
	for(AActor* Actor : SpawnedObjects)
	{
		
		TArray<UProjectileMove*> ProjectileMoveComponents;
		Actor->GetComponents(ProjectileMoveComponents);
		for (UProjectileMove* ProjectileMove : ProjectileMoveComponents)
		{
			if (ProjectileMove)
			{
				ProjectileMove->InitializeProjectile(Owner);
			}
		}
	}

	// Reset cooldown
	ResetCD();
}

void FMoveInstance::ResetCD()
{
	const float BaseCD = MoveData->BaseCooldown;
	const float Haste = Stats->GetStat(EStatEnum::Haste).GetCurrentValue();
	RemainingCD = BaseCD/(1+Haste/100.f);
}

bool FMoveInstance::IsValid() const
{
	return MoveData != nullptr;
}
