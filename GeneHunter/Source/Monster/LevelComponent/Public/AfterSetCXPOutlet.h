#pragma once
#include "EffectOutlet_Base.h"

#include "AfterSetCXPOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetCXPSignature, const int, OldCXP, const int, NewCXP);

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetCXPSignature Delegate;
	
};
