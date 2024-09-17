#include "MoveInstance.h"

#include "ProjectileMove.h"

void FMoveInstance::Initialize(AActor* Owner)
{

	// Usability
	if (MoveData->UsabilityScheme)
	{
		UsabilityScheme = NewObject<UMoveUsabilityScheme>(Owner, MoveData->UsabilityScheme);
		UsabilityScheme->Initialize(Owner);
	}

	// Spawn schemes
	for(TSubclassOf<UActorSpawnScheme> SpawnClass : MoveData->SpawnOnCast)
	{
		SpawnSchemesOnCast.Add(NewObject<UActorSpawnScheme>(Owner, SpawnClass));
	}
}

void FMoveInstance::Execute(AActor* Owner)
{

	// Spawn some Actors
	for(UActorSpawnScheme* SpawnScheme : SpawnSchemesOnCast)
	{
		// Shouldn't be null, but you never know!
		if (SpawnScheme)
		{

			// Do the spawning
			TArray<AActor*> FreshActors = {};
			SpawnScheme->Spawn(Owner, FreshActors);

			// Initialize projectiles
			for(AActor* Actor : FreshActors)
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
