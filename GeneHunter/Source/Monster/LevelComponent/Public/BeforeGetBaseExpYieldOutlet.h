#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "BeforeGetBaseExpYieldOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetBaseExpYieldSignature, const float, OriginalYield, float&, Yield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeGetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetBaseExpYieldSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeGetBaseExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetBaseExpYieldDelegate> Delegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(EDelegateTriggerTiming::Before, FBeforeGetBaseExpYieldDelegate,
		Delegates, Delegate, const float,float&);
};
