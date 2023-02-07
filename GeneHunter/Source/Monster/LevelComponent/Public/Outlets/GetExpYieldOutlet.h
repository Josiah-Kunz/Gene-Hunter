#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "GetExpYieldOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_FourParams(FBeforeGetExpYieldSignature,
	const float, OriginalYield,
	float&, ReturnedYield,
	const uint16, DefeatedLevel,
	const uint16, VictoriousLevel
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeGetExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetExpYieldSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_FourParams(FAfterGetExpYieldSignature,
	const float, OriginalYield,
	const float, ReturnedYield,
	const uint16, DefeatedLevel,
	const uint16, VictoriousLevel
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterGetExpYieldDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetExpYieldSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FGetExpYieldOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetExpYieldDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(Before, FBeforeGetExpYieldDelegate,
		BeforeDelegates, Delegate,
		const float, float&, const uint16, const uint16
		);

	UPROPERTY()
	TArray<FAfterGetExpYieldDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(After, FAfterGetExpYieldDelegate,
		AfterDelegates, Delegate,
		const float, const float, const uint16, const uint16
		);
};

#pragma endregion