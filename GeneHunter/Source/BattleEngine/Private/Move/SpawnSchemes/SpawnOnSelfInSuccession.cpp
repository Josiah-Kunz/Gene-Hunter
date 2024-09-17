#include "SpawnOnSelfInSuccession.h"

#include "ExpirationComponent.h"
#include "ProjectileDependent.h"
#include "TimerManager.h"

USpawnOnSelfInSuccession::USpawnOnSelfInSuccession()
{
	CurrentIndex = 0;
}

AActor* USpawnOnSelfInSuccession::SpawnSingle()
{

	// "Spawn" the next one
	AActor* NewSpawn = ActorsToSpawn[CurrentIndex];
	const FVector OwnerLocation = Owner->GetActorLocation();
	NewSpawn->SetActorLocation(OwnerLocation);
	SetActive(NewSpawn, true);
	

	// Keep track!
	CurrentIndex++;
	if (CurrentIndex >= Actors.Num())
	{
		StopTick();
	}

	// Return
	return NewSpawn;
}

void USpawnOnSelfInSuccession::Spawn(AActor* NewOwner, TArray<AActor*>& SpawnedActors)
{
	
	// Guard
	CurrentIndex = 0;

	// Assign owner
	Owner = NewOwner;

	// Spawn (initializes + adds to list)
	 Super::Spawn(NewOwner, SpawnedActors);

	// Turn off all
	for(AActor* SpawnedActor : SpawnedActors)
	{
		SetActive(SpawnedActor, false);
	}

	// Assign
	ActorsToSpawn = SpawnedActors;

	// Set the first to active
	SpawnSingle();

	// Time
	StartTick();
}

void USpawnOnSelfInSuccession::Tick(float DeltaTime)
{
	SpawnSingle();
}

void USpawnOnSelfInSuccession::StartTick()
{
	const UWorld* World = GetWorld();
	if (GWorld) 
	{
		GWorld->GetTimerManager().SetTimer(TickTimerHandle, this, &USpawnOnSelfInSuccession::HandleTick,
			TimeBetweenSpawns, true);
	}
}

void USpawnOnSelfInSuccession::StopTick()
{
	const UWorld* World = GetWorld();
	if (GWorld)
	{
		GWorld->GetTimerManager().ClearTimer(TickTimerHandle);
	}
}

void USpawnOnSelfInSuccession::HandleTick()
{
	Tick(TimeBetweenSpawns);
}

void USpawnOnSelfInSuccession::SetActive(AActor* Actor, const bool bIsActive) const
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
					ProjectileDependent->Caster = Owner;
					ProjectileDependent->Enable();
				} else
				{
					ProjectileDependent->Disable();
				}

			// Expiration component
				/*
			} else if (bIsActive && Component->IsA(UExpirationComponent::StaticClass()))
			{
				UExpirationComponent* ExpirationComponent = Cast<UExpirationComponent>(Component);
				UE_LOG(LogTemp, Warning, TEXT("Resetting!"))
				ExpirationComponent->Reset();
				*/
			// All other components
			} else
			{
				Component->SetComponentTickEnabled(bIsActive);
			}
		}
	}

}
