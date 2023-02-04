#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "BeforeSetBaseExpYieldOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeSetBaseExpYieldSignature,
	const float, OldYield, float&, AttemptedYield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetBaseExpYieldSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetBaseExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetBaseExpYieldDelegate> Delegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(EDelegateTriggerTiming::Before, FBeforeSetBaseExpYieldDelegate,
		Delegates, Delegate, const float, float&);
};
