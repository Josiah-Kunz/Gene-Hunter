#include "ActorSpawnScheme.h"

void UActorSpawnScheme::Spawn(AActor* NewOwner, TArray<AActor*>& SpawnedActors)
{
	Owner = NewOwner;
	UWorld* World = Owner->GetWorld();
	for(TSubclassOf<AActor> ActorClass : Actors)
	{
		AActor* NewActor = World->SpawnActor(ActorClass);
		SpawnedActors.Add(NewActor);
	}
}
