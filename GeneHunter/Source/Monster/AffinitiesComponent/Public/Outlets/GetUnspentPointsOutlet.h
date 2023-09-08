#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "GetUnspentPointsOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetUnspentPointsSignature,
	const uint8, OriginalPoints,
	uint8&, ReturnedPoints);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FBeforeGetUnspentPointsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetUnspentPointsSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetUnspentPointsSignature,
	const uint8, OriginalPoints,
	const uint8, ReturnedPoints);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FAfterGetUnspentPointsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetUnspentPointsSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FGetUnspentPointsOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetUnspentPointsDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetUnspentPointsDelegate,
		BeforeDelegates, Delegate, const uint8, uint8&);

	UPROPERTY()
	TArray<FAfterGetUnspentPointsDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetUnspentPointsDelegate,
		AfterDelegates, Delegate, const uint8, const uint8);
};

#pragma endregion