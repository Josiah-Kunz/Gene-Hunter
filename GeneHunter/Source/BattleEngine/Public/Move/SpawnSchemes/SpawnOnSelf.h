#pragma once

#include "CoreMinimal.h"
#include "ActorSpawnScheme.h"
#include "SpawnOnSelf.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API USpawnOnSelf : public UActorSpawnScheme
{
	GENERATED_BODY()

public:

	virtual void Spawn(AActor* NewOwner, TArray<AActor*>& SpawnedActors) override;
	
};
