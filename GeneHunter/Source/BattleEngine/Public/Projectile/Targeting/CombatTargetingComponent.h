#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatTargetingComponent.generated.h"


UCLASS(Abstract, Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UCombatTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatTargetingComponent();

	virtual FVector GetAttackVector();

};
