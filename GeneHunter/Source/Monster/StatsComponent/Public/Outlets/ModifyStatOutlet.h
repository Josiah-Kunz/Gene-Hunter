#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"
#include "StatRandParams.h"

#include "ModifyStatOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_FiveParams(FBeforeModifyStatSignature,
	const EStatEnum, TargetStat,
	const EStatValueType, ValueType,
	const EModificationMode, Mode,
	const float, OriginalValue,
	float&, AttemptedValue
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FBeforeModifyStatDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeModifyStatSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_FiveParams(FAfterModifyStatSignature,
	const EStatEnum, TargetStat,
	const EStatValueType, ValueType,
	const EModificationMode, Mode,
	const float, OriginalValue,
	const float, NewValue
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FAfterModifyStatDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterModifyStatSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FModifyStatOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeModifyStatDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FiveParams(Before, FBeforeModifyStatDelegate,
		BeforeDelegates, Delegate,
		const EStatEnum,
		const EStatValueType,
		const EModificationMode,
		const float,
		float&
		);

	UPROPERTY()
	TArray<FAfterModifyStatDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FiveParams(After, FAfterModifyStatDelegate,
		AfterDelegates, Delegate,
		const EStatEnum,
		const EStatValueType,
		const EModificationMode,
		const float,
		const float
		);
};

#pragma endregion