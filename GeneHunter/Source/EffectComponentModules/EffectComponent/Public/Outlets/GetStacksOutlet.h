#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "GetStacksOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetStacksSignature,
	const uint16, OGStacks,
	int32&, ReturnedStacks
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FBeforeGetStacksDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetStacksSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetStacksSignature,
	const uint16, OGStacks,
	const int32, ReturnedStacks
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FAfterGetStacksDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetStacksSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FGetStacksOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetStacksDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetStacksDelegate,
		BeforeDelegates, Delegate,
		const uint16, int32&
		);

	UPROPERTY()
	TArray<FAfterGetStacksDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetStacksDelegate,
		AfterDelegates, Delegate,
		const uint16, const int32
		);
};

#pragma endregion