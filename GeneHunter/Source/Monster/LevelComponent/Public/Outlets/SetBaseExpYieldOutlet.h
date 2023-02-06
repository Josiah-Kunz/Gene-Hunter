#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "SetBaseExpYieldOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeSetBaseExpYieldSignature,
	const float, OldYield,
	float&, AttemptedYield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetBaseExpYieldSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetBaseExpYieldSignature,
	const float, OldYield,
	const float, NewYield);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetBaseExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetBaseExpYieldSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetBaseExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetBaseExpYieldDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeSetBaseExpYieldDelegate,
		BeforeDelegates, Delegate, const float, float&);

	UPROPERTY()
	TArray<FAfterSetBaseExpYieldDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterSetBaseExpYieldDelegate,
		AfterDelegates, Delegate, const float, const float);
};

#pragma endregion