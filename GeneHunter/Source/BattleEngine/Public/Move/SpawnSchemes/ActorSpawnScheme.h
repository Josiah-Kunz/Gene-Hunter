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
	virtual TArray<AActor*> Spawn(AActor* Owner);
	
};
