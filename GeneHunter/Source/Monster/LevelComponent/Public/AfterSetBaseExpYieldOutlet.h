#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "AfterSetBaseExpYieldOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetBaseExpYieldSignature,
	const float, OldYield, const float, NewYield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetBaseExpYieldSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetBaseExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FAfterSetBaseExpYieldDelegate> Delegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(EDelegateTriggerTiming::After, FAfterSetBaseExpYieldDelegate,
		Delegates, Delegate, const float, const float);
};
