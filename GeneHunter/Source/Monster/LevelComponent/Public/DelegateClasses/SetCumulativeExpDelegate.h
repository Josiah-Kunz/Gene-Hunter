#pragma once

#include "SetCumulativeExpDelegate.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_DELEGATE_TwoParams(FSetCumulativeExpDelegate, int, CurrentCXP, int&, AttemptedCXP);

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCumulativeExpWrapper
{
	GENERATED_BODY()

	virtual ~FSetCumulativeExpWrapper() = default;
	
public:
	
	FSetCumulativeExpDelegate Delegate;

	UPROPERTY()
	float Priority = 50;
};
