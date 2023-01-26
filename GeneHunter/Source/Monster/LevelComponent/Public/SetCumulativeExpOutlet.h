#pragma once

#include "SetCumulativeExpOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FSetCumulativeExpSignature, int, CurrentCXP, int&, AttemptedCXP);

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCumulativeExpOutlet
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FSetCumulativeExpSignature SetCumulativeExpDelegate;
	
};
