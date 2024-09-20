#include "MoveInstance.h"

#include "ProjectileMove.h"

void FMoveInstance::Initialize(AActor* Owner)
{

	// Setup variables
	UWorld* World = Owner->GetWorld();
	const FVector SpawnLocation = Owner->GetActorLocation();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;

	// Create instanced schemes and initialize them
	for(TSubclassOf<AMoveUsabilityScheme> UsabilityClass : MoveData->UsabilitySchemes)
	{
		if (UsabilityClass)
		{
			AMoveUsabilityScheme* NewUsabilityScheme = World->SpawnActor<AMoveUsabilityScheme>(
				UsabilityClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams
			);
			NewUsabilityScheme->Initialize(Owner);
			UsabilitySchemes.Add(NewUsabilityScheme);
		}
	}

	// SpawnOnCast
	for(TSubclassOf<UActorSpawnScheme> SpawnClass : MoveData->SpawnOnCast)
	{
		UActorSpawnScheme* NewSpawnScheme = NewObject<UActorSpawnScheme>(Owner, SpawnClass);
		SpawnSchemesOnCast.Add(NewSpawnScheme);
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
			for(const AActor* Actor : FreshActors)
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
