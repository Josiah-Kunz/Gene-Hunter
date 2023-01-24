#pragma once

#include "SetCumulativeExpDelegate.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCumulativeExpDelegate
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_DELEGATE_TwoParams(FDelegate, int, CurrentCXP, int&, AttemptedCXP);
	
	FDelegate Delegate;

	UPROPERTY()
	float Priority = 50;
};
