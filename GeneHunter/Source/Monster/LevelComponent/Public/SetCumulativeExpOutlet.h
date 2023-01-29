#pragma once

#include "SetCumulativeExpOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FSetCumulativeExpSignature, const int, OldCXP, const int, NewCXP);

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
