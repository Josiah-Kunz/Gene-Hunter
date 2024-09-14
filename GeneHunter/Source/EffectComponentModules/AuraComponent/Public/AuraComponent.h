#pragma once

#include "EffectComponent.h"

#include "AuraComponent.generated.h"

/**
 * A UEffectComponent that is visible and purgeable, but not timed.
 */
UCLASS(Abstract, ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class AURACOMPONENT_API UAuraComponent : public UEffectComponent
{
	GENERATED_BODY()


	virtual bool IsPurgeable() const override;

	virtual bool IsVisibleToUI() const override;
};
