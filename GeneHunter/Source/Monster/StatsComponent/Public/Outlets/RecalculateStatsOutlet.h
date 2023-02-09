#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"
#include "StatRandParams.h"

#include "RecalculateStatsOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_FourParams(FBeforeRecalculateStatsSignature,
	const EStatEnum, TargetStat,
	const bool, bResetCurrent,
	const float, OriginalCurrent,
	const float, OriginalPermanent
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FBeforeRecalculateStatsDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeRecalculateStatsSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_FourParams(FAfterRecalculateStatsSignature,
	const EStatEnum, TargetStat,
	const bool, bResetCurrent,
	const float, OriginalCurrent,
	const float, OriginalPermanent
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FAfterRecalculateStatsDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterRecalculateStatsSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct LEVELCOMPONENT_API FRecalculateStatsOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeRecalculateStatsDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(Before, FBeforeRecalculateStatsDelegate,
		BeforeDelegates, Delegate,
		const EStatEnum, const bool, const float, const float
		);

	UPROPERTY()
	TArray<FAfterRecalculateStatsDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(After, FAfterRecalculateStatsDelegate,
		AfterDelegates, Delegate,
		const EStatEnum, const bool, const float, const float
		);
};

#pragma endregion