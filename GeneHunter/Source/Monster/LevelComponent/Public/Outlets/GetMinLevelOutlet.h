#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "GetMinLevelOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeGetMinLevelSignature,
	const uint16, DefaultMin,
	int32&, AttemptedMin);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeGetMinLevelDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetMinLevelSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterGetMinLevelSignature,
	const uint16, DefaultMin,
	const int32, AttemptedMin);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterGetMinLevelDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetMinLevelSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FGetMinLevelOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetMinLevelDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeGetMinLevelDelegate,
		BeforeDelegates, Delegate, const uint16, int32&);

	UPROPERTY()
	TArray<FAfterGetMinLevelDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterGetMinLevelDelegate,
		AfterDelegates, Delegate, const uint16, const int32);
};

#pragma endregion