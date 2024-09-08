#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "GetExpirationTimeOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetExpirationTimeSignature,
	const float, UnmodifiedTime,
	float&, ReturnedTime
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FBeforeGetExpirationTimeDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetExpirationTimeSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetExpirationTimeSignature,
	const float, UnmodifiedTime,
	const float, ReturnedTime
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FAfterGetExpirationTimeDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetExpirationTimeSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FGetExpirationTimeOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetExpirationTimeDelegate> BeforeDelegates;

	UPROPERTY()
	TArray<FAfterGetExpirationTimeDelegate> AfterDelegates;

public:
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetExpirationTimeDelegate,
		BeforeDelegates, Delegate,
		const float, float&
		);
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetExpirationTimeDelegate,
		AfterDelegates, Delegate,
		const float, const float
		);
};

#pragma endregion