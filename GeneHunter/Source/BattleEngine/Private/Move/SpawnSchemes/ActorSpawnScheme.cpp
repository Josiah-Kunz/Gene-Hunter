#include "ActorSpawnScheme.h"

TArray<AActor*> UActorSpawnScheme::Spawn(AActor* Owner)
{
	UWorld* World = Owner->GetWorld();
	TArray<AActor*> SpawnedActors = {};
	for(TSubclassOf<AActor> ActorClass : Actors)
	{
		AActor* NewActor = World->SpawnActor(ActorClass);
		SpawnedActors.Add(NewActor);
	}
	return SpawnedActors;
}
