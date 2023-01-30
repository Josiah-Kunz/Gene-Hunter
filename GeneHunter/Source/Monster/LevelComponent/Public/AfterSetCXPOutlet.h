#pragma once

#include "AfterSetCXPOutlet.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetCXPSignature, const int, OldCXP, const int, NewCXP);

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPOutlet
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetCXPSignature AfterSetCXPDelegate;
	
};
