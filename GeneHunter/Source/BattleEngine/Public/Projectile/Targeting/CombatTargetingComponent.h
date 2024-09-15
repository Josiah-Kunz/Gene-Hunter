#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "Components/ActorComponent.h"
#include "CombatTargetingComponent.generated.h"


UCLASS(Abstract, Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UCombatTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UCombatTargetingComponent();

	/**
	 * Intended to return a Vector direction to attack.
	 * @return 
	 */
	virtual FVector GetAttackVector();

	/**
	 * Returns a CombatStatsComponent, presumably so you can shoot at it, but that's really, like, up to you man.
	 * @return Careful---this could be nullptr!
	 */
	virtual UCombatStatsComponent* GetTarget();

};
