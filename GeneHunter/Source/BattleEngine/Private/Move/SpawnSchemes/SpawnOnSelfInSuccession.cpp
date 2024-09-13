#include "SpawnOnSelfInSuccession.h"

#include "ProjectileDependent.h"
#include "TimerManager.h"

USpawnOnSelfInSuccession::USpawnOnSelfInSuccession()
{
	CurrentIndex = 0;
}

AActor* USpawnOnSelfInSuccession::SpawnSingle()
{

	// "Spawn" the next one
	AActor* NewSpawn = SpawnedActors[CurrentIndex];
	SetActive(NewSpawn, true);
	const FVector OwnerLocation = Owner->GetActorLocation();
	NewSpawn->SetActorLocation(OwnerLocation);

	// Keep track!
	CurrentIndex++;
	if (CurrentIndex >= Actors.Num())
	{
		StopTick();
	}

	// Return
	return NewSpawn;
}

TArray<AActor*> USpawnOnSelfInSuccession::Spawn(AActor* NewOwner)
{
	
	// Guard
	if (CurrentIndex != 0)
	{
		return {};
	}

	// Assign owner
	Owner = NewOwner;

	// Spawn (initializes + adds to list)
	SpawnedActors = Super::Spawn(NewOwner);

	// Turn off all
	for(AActor* SpawnedActor : SpawnedActors)
	{
		SetActive(SpawnedActor, false);
	}

	// Set the first to active
	SpawnSingle();

	// Time
	StartTick();

	// Return
	return SpawnedActors;
}

void USpawnOnSelfInSuccession::Tick(float DeltaTime)
{
	SpawnSingle();
}

void USpawnOnSelfInSuccession::StartTick()
{
	const UWorld* World = GetWorld();
	if (World) 
	{
		World->GetTimerManager().SetTimer(TickTimerHandle, this, &USpawnOnSelfInSuccession::HandleTick,
			TimeBetweenSpawns, true);
	}
}

void USpawnOnSelfInSuccession::StopTick()
{
	const UWorld* World = GetWorld();
	if (World)
	{
		World->GetTimerManager().ClearTimer(TickTimerHandle);
	}
}

void USpawnOnSelfInSuccession::HandleTick()
{
	Tick(TimeBetweenSpawns);
}

void USpawnOnSelfInSuccession::SetActive(AActor* Actor, const bool bIsActive)
{

	// The actor itself
	Actor->SetActorHiddenInGame(!bIsActive);
	Actor->SetActorEnableCollision(bIsActive);
	Actor->SetActorTickEnabled(bIsActive);

	// Components
	TArray<UActorComponent*> Components;
	Actor->GetComponents(Components);
	for (UActorComponent* Component : Components)
	{
		if (Component->IsRegistered())
		{

			// Special for UProjectileDependents
			if (Component->IsA(UProjectileDependent::StaticClass()))
			{
				UProjectileDependent* ProjectileDependent = Cast<UProjectileDependent>(Component);
				if (bIsActive)
				{
					ProjectileDependent->Enable();
				} else
				{
					ProjectileDependent->Disable();
				}

			// All other components
			} else
			{
				Component->SetComponentTickEnabled(bIsActive);
			}
		}
	}

}
