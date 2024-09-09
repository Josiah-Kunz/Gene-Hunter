#include "SpawnOnSelfInSuccession.h"

#include "TimerManager.h"

USpawnOnSelfInSuccession::USpawnOnSelfInSuccession()
{
	CurrentIndex = 0;
}

AActor* USpawnOnSelfInSuccession::SpawnSingle()
{

	// Spawn the Actor
	UWorld* World = Owner->GetWorld();
	AActor* NewActor = World->SpawnActor(Actors[CurrentIndex]);
	NewActor->SetActorLocation(Owner->GetActorLocation());

	// Keep track!
	CurrentIndex++;
	if (CurrentIndex >= Actors.Num())
	{
		StopTick();
	}

	// Return
	return NewActor;
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

	// Spawn an Actor
	AActor* SpawnedActor = SpawnSingle();

	// Time
	StartTick();

	// Return
	return {SpawnedActor};
}

void USpawnOnSelfInSuccession::Tick(float DeltaTime)
{
	SpawnSingle();
}

void USpawnOnSelfInSuccession::StartTick()
{
	if (GWorld) 
	{
		GWorld->GetTimerManager().SetTimer(TickTimerHandle, this, &USpawnOnSelfInSuccession::HandleTick,
			TimeBetweenSpawns, true);
	}
}

void USpawnOnSelfInSuccession::StopTick()
{
	if (GWorld)
	{
		GWorld->GetTimerManager().ClearTimer(TickTimerHandle);
	}
}

void USpawnOnSelfInSuccession::HandleTick()
{
	Tick(TimeBetweenSpawns);
}
