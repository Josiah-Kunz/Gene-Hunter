#pragma once

#include "EffectDelegate_Base.generated.h"

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something. This is that something. It also gives
 * delegates a Priority so that execution can be ordered and predictable.
 *
 * When inheriting from this, you need to:
 *	- DECLARE_DYNAMIC_DELEGATE_xParams(FSignature, ...) outside the inherited struct definition
*	- Declare a public UPROPERTY() FSignature Delegate;
 */
USTRUCT(Blueprintable)
struct EFFECTABLECOMPONENT_API FEffectDelegate_Base
{
	GENERATED_BODY()

public:
	
	/** Affects effect execution order (see UEffectComponent::GetPriority). */
	UPROPERTY()
	float Priority = 50;
	
};
