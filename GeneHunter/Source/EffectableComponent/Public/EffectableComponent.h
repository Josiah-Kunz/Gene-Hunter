#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectableComponent.generated.h"

/**
 * The base class for so-called "effectable" components, which can house effects. Example: UCombatStatsComponent should
 *	inherit from this, as you can create effects that "plug in" to UCombatStatsComponent.
 */
UCLASS()
class EFFECTABLECOMPONENT_API UEffectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	/**
	 * Priority for "intrinsic" delegates. These delegates are defined in C# and hence don't have an EffectComponent.
	 * An example is UCombatStatsComponent::UpdateStatsAfterLevel. This should always happen regardless of, e.g., buffs.
	 */
	inline static constexpr float IntrinsicPriority = -999999999;

	/**
	 * Priority for UI delegates (for example, a health bar).
	 */
	inline static constexpr float UIPriority = 0;
	
};
