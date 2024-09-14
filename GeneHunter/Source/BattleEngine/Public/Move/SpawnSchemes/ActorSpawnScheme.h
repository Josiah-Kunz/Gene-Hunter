#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"

#include "ActorSpawnScheme.generated.h"

/**
 * A base class for the details of spawning Actors. For example, maybe you want to spawn a single Actor from a list. Or
 * maybe you want to randomly spawn 1, 2, or 3 copies of an Actor at 3 different positions. Inherit from this and
 * customize your implementation!
 *
 * By default, this class simply spawns all of the provided Actors at the World origin.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UActorSpawnScheme : public UObject
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
	virtual TArray<AActor*> Spawn(AActor* NewOwner);

	/**
	 * This could be optimized. It's spawning not only instances of UActorSpawnScheme and then deleting them, but it's 
	 * also spawning actors themselves. My issue with object pooling is that this method may very well be used to
	 * randomly spawn 1, 2, or 3 objects. Should we just create 1, 2, or 3 objects and de/activate them when we need
	 * them? Probably. But let's make sure we have the need.
	 * @return The Actors that spawned.
	 */
	static TArray<AActor*> SpawnActors(AActor* Owner, const TArray<TSubclassOf<UActorSpawnScheme>>& ActorsToSpawn);

protected:

	UPROPERTY()
	AActor* Owner;
	
};
