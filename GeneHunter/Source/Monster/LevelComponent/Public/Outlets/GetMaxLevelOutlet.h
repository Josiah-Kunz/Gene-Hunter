#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "GetMaxLevelOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetMaxLevelSignature,
	const uint16, DefaultMax,
	int32&, AttemptedMax);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeGetMaxLevelDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetMaxLevelSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetMaxLevelSignature,
	const uint16, DefaultMax,
	const int32, AttemptedMax);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterGetMaxLevelDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetMaxLevelSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FGetMaxLevelOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetMaxLevelDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetMaxLevelDelegate,
		BeforeDelegates, Delegate, const uint16, int32&);

	UPROPERTY()
	TArray<FAfterGetMaxLevelDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetMaxLevelDelegate,
		AfterDelegates, Delegate, const uint16, const int32);
};

#pragma endregion