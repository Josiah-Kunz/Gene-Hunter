// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnOnSelf.h"

/* TODO:
 * If we ever add body parts, we need to search the Owner for a body part designator and act accordingly.
 */

void USpawnOnSelf::Spawn(AActor* NewOwner, TArray<AActor*>& SpawnedActors)
{
	Super::Spawn(NewOwner, SpawnedActors);
	const FVector OwnerLocation = Owner->GetActorLocation();
	for(AActor* SpawnedActor : SpawnedActors)
	{
		SpawnedActor->SetActorLocation(OwnerLocation);
	}
}
