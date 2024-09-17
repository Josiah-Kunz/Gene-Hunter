#pragma once

#include "CoreMinimal.h"
#include "SpawnOnSelf.h"
#include "SpawnOnSelfInSuccession.generated.h"

/**
 * Each Actor in the list spawns on self with a delay.
 */
UCLASS(Abstract)
class BATTLEENGINE_API USpawnOnSelfInSuccession : public USpawnOnSelf
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnActor")
	float TimeBetweenSpawns = 0.1f;

	USpawnOnSelfInSuccession();

	/**
	 * Spawns a single Actor based on the Actors Index.
	 * @return 
	 */
	UFUNCTION(Blueprintable)
	AActor* SpawnSingle();

	virtual void Spawn(AActor* NewOwner, TArray<AActor*>& SpawnedActors) override;

	/**
	 * UObjects can't normally tick, but we have our ways of making them!
	 * @param DeltaTime 
	 */
	UFUNCTION(Blueprintable)
	virtual void Tick(float DeltaTime);

	UFUNCTION(Blueprintable)
	void StartTick();

	UFUNCTION(Blueprintable)
	void StopTick();

protected:

	UFUNCTION(Blueprintable)
	void HandleTick();

private:

	UPROPERTY()
	uint16 CurrentIndex = 0;

	UPROPERTY()
	TArray<AActor*> ActorsToSpawn;

	/**
	 * This handles ticking.
	 */
	FTimerHandle TickTimerHandle;

	void SetActive(AActor* Actor, const bool bIsActive) const;
	
};
