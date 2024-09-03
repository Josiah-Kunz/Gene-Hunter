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

	virtual TArray<AActor*> Spawn(AActor* Owner) override;
	
};
