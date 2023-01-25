#pragma once

#include "SetCumulativeExpDelegate.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSetCumulativeExpDelegateDelegate, int, CurrentCXP, int&, AttemptedCXP);

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCumulativeExpDelegate
{
	GENERATED_BODY()

public:
	
	FSetCumulativeExpDelegateDelegate Delegate;

	UPROPERTY()
	float Priority = 50;
};
