#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "AfterGetBaseExpYieldOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetBaseExpYieldSignature,
	const float, OriginalYield, const float, ReturnedYield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterGetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetBaseExpYieldSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterGetBaseExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FAfterGetBaseExpYieldDelegate> Delegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(EDelegateTriggerTiming::After, FAfterGetBaseExpYieldDelegate,
		Delegates, Delegate, const float, const float);
};
