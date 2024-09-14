#pragma once

#include "IntrinsicEffectComponent.h"

#include "TalentEffectComponent.generated.h"

/**
 * A UIntrinsicEffectComponent that is assigned once a Talent is selected. Note that it's not up to this class to
 * assign/unassign its own effect.
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class TALENTEFFECTCOMPONENT_API UTalentEffectComponent : public UIntrinsicEffectComponent
{
	GENERATED_BODY()

};
