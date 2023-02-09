#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "SetCXPOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_TwoParams(FBeforeSetCXPSignature,
	const uint32, OldCXP,
	int32&, AttemptedCXP
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeSetCXPDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetCXPSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_TwoParams(FAfterSetCXPSignature,
	const uint32, OldCXP,
	const int32, NewCXP
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterSetCXPDelegate : public FEffectDelegate_Base
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
struct LEVELCOMPONENT_API FSetCXPOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetCXPDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(Before, FBeforeSetCXPDelegate,
		BeforeDelegates, Delegate,
		const uint32, int32&
		);

	UPROPERTY()
	TArray<FAfterSetCXPDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_TwoParams(After, FAfterSetCXPDelegate,
		AfterDelegates, Delegate,
		const uint32, const int32
		);
};

#pragma endregion