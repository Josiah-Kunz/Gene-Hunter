#include "ActorSpawnScheme.h"

TArray<AActor*> UActorSpawnScheme::Spawn(AActor* NewOwner)
{
	Owner = NewOwner;
	UWorld* World = Owner->GetWorld();
	TArray<AActor*> SpawnedActors = {};
	for(TSubclassOf<AActor> ActorClass : Actors)
	{
		AActor* NewActor = World->SpawnActor(ActorClass);
		SpawnedActors.Add(NewActor);
	}
	return SpawnedActors;
}

TArray<AActor*> UActorSpawnScheme::SpawnActors(AActor* Owner, const TArray<TSubclassOf<UActorSpawnScheme>>& ActorsToSpawn)
{
	// Setup
	TArray<AActor*> SpawnedObjects = {};

	// Spawn based on the data rules
	for(const TSubclassOf<UActorSpawnScheme> SpawnActorClass : ActorsToSpawn)
	{
		// Shouldn't be null, but you never know!
		if (SpawnActorClass)
		{

			// Get an actual instance of the class.
			UActorSpawnScheme* SpawnActorInstance = NewObject<UActorSpawnScheme>(Owner, SpawnActorClass);
			TArray<AActor*> FreshActors = SpawnActorInstance->Spawn(Owner);

			// Add to the whole collection
			for(AActor* Actor : FreshActors)
			{
				SpawnedObjects.Add(Actor);
			}

			// Not sure if this is necessary---is the UObject attached to the Owner and protected from gc?
			SpawnActorInstance->ConditionalBeginDestroy();
		}
	}

	// Return
	return SpawnedObjects;
}
