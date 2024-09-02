// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnOnSelf.h"

/* TODO:
 * If we ever add body parts, we need to search the Owner for a body part designator and act accordingly.
 */

TArray<AActor*> USpawnOnSelf::Spawn(AActor* Owner)
{
	TArray<AActor*> SpawnedActors = Super::Spawn(Owner);
	const FVector OwnerLocation = Owner->GetActorLocation();
	for(AActor* SpawnedActor : SpawnedActors)
	{
		SpawnedActor->SetActorLocation(OwnerLocation);
	}
	return SpawnedActors;
}
