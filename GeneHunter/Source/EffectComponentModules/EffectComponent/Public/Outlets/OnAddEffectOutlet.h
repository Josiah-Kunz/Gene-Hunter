#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "OnAddEffectOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_OneParam(FBeforeOnAddEffectSignature,
	const UEffectComponent*, EffectToAdd
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FBeforeOnAddEffectDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeOnAddEffectSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_OneParam(FAfterOnAddEffectSignature,
	const UEffectComponent*, AddedEffect
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FAfterOnAddEffectDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterOnAddEffectSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FOnAddEffectOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeOnAddEffectDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_OneParam(Before, FBeforeOnAddEffectDelegate,
		BeforeDelegates, Delegate,
		const UEffectComponent*
		);

	UPROPERTY()
	TArray<FAfterOnAddEffectDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_OneParam(After, FAfterOnAddEffectDelegate,
		AfterDelegates, Delegate,
		const UEffectComponent*
		);
};

#pragma endregion