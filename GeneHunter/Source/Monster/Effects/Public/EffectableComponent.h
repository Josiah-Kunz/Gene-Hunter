

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectableComponent.generated.h"

/**
 * The base class for so-called "effectable" components, which can house effects. Example: UStatsComponent should
 *	inherit from this, as you can create effects that "plug in" to UStatsComponent.
 */
UCLASS()
class EFFECTS_API UEffectableComponent : public UActorComponent
{
	GENERATED_BODY()
	
};
