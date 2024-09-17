#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MoveUsabilityScheme.generated.h"

/**
 * Sets conditions on when a Move can or cannot be used. Does not count cooldowns.
 * For example, an "Execution" Move might only be usable when the target has <20% health.
 */
UCLASS(Abstract, Blueprintable)
class BATTLEENGINE_API UMoveUsabilityScheme : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY()
	AActor* Owner;

	UFUNCTION(BlueprintNativeEvent, Category="MoveData")
	void Initialize(AActor* NewOwner);
	
	UFUNCTION(BlueprintNativeEvent, Category="MoveData")
	bool IsUsable(AActor* MoveOwner);
};
