#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "AfterSetCXPOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetCXPSignature, const uint32, OldCXP, const uint32, NewCXP);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetCXPSignature Delegate;
	
};

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FAfterSetCXPDelegate> Delegates;
	
	DECLARE_AFTER_OUTLET_FUNCTIONS_TwoParams(FAfterSetCXPDelegate, Delegates, Delegate, const uint32, const uint32);
};
