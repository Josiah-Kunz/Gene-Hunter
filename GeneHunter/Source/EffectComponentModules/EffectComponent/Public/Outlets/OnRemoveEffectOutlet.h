#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "OnRemoveEffectOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_OneParam(FBeforeOnRemoveEffectSignature,
	const UEffectComponent*, EffectToRemove
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FBeforeOnRemoveEffectDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeOnRemoveEffectSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_OneParam(FAfterOnRemoveEffectSignature,
	const UEffectComponent*, RemovedEffect
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FAfterOnRemoveEffectDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterOnRemoveEffectSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FOnRemoveEffectOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeOnRemoveEffectDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_OneParam(Before, FBeforeOnRemoveEffectDelegate,
		BeforeDelegates, Delegate,
		const UEffectComponent*
		);

	UPROPERTY()
	TArray<FAfterOnRemoveEffectDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_OneParam(After, FAfterOnRemoveEffectDelegate,
		AfterDelegates, Delegate,
		const UEffectComponent*
		);
};

#pragma endregion