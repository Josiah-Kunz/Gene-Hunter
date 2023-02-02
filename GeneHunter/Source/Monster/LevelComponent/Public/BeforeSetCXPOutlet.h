#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "BeforeSetCXPOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeSetCXPSignature, const uint32, OldCXP, int32&, AttemptedCXP);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetCXPDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetCXPSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetCXPOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetCXPDelegate> Delegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(EDelegateTriggerTiming::Before, FBeforeSetCXPDelegate, Delegates, Delegate, const uint32, int32&);
};
