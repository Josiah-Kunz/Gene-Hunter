#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectableComponent.generated.h"

/**
 * The base class for so-called "effectable" components, which can house effects. Example: UStatsComponent should
 *	inherit from this, as you can create effects that "plug in" to UStatsComponent.
 */
UCLASS()
class EFFECTABLECOMPONENT_API UEffectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	/**
	 * Priority for "intrinsic" delegates. These delegates are defined in C# and hence don't have an EffectComponent.
	 * An example is UStatsComponent::UpdateStatsAfterLevel. This should always happen regardless of, e.g., buffs.
	 */
	inline static constexpr float IntrinsicPriority = -999999999;
	
};
