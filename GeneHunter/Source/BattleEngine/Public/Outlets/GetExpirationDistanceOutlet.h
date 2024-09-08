#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "GetExpirationDistanceOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetExpirationDistanceSignature,
	const float, UnmodifiedDistance,
	float&, ReturnedDistance
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FBeforeGetExpirationDistanceDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetExpirationDistanceSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetExpirationDistanceSignature,
	const float, UnmodifiedDistance,
	const float, ReturnedDistance
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FAfterGetExpirationDistanceDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetExpirationDistanceSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct BATTLEENGINE_API FGetExpirationDistanceOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetExpirationDistanceDelegate> BeforeDelegates;

	UPROPERTY()
	TArray<FAfterGetExpirationDistanceDelegate> AfterDelegates;

public:
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetExpirationDistanceDelegate,
		BeforeDelegates, Delegate,
		const float, float&
		);
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetExpirationDistanceDelegate,
		AfterDelegates, Delegate,
		const float, const float
		);
};

#pragma endregion