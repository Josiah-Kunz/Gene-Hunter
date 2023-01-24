#pragma once

#include "GetBaseExpYieldDelegate.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FGetBaseExpYieldDelegate
{
	GENERATED_BODY()

public:

	DECLARE_DYNAMIC_DELEGATE_OneParam(FDelegate, float&, BaseExpYield);
	
	FDelegate Delegate;

	UPROPERTY()
	float Priority = 50;
};
