#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "SetCXPOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FBeforeSetCXPSignature,
	const uint32, OldCXP,
	const int32, InputCXP,
	int32&, AttemptedCXP
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetCXPDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetCXPSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAfterSetCXPSignature,
	const uint32, OldCXP,
	const int32, InputCXP,
	const int32, NewCXP
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetCXPSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FSetCXPOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetCXPDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(Before, FBeforeSetCXPDelegate,
		BeforeDelegates, Delegate,
		const uint32, const int32, int32&
		);

	UPROPERTY()
	TArray<FAfterSetCXPDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(After, FAfterSetCXPDelegate,
		AfterDelegates, Delegate,
		const uint32, const int32, const int32
		);
};

#pragma endregion