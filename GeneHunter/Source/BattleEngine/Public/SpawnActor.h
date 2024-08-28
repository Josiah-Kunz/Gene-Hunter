#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SpawnActor.generated.h"

/**
 * A base class for spawning Actors. For example, maybe you want to spawn a single Actor from a list. Or maybe you want
 * to randomly spawn 1, 2, or 3 copies of an Actor. Inherit from this and customize your implementation!
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API USpawnActor : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="SpawnActor")
	TArray<TSubclassOf<AActor>> Actors;

	/**
	 * Spawns Actor(s) according to the inherited class.
	 * @return The Actors that spawned.
	 */
	UFUNCTION(BlueprintCallable, Category="SpawnActor")
	virtual TArray<AActor*> Spawn(UWorld* World);
	
};
