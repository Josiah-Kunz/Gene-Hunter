#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"
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
struct COMBATSTATSCOMPONENT_API FBeforeRecalculateStatsDelegate : public FEffectDelegate
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
struct COMBATSTATSCOMPONENT_API FAfterRecalculateStatsDelegate : public FEffectDelegate
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
struct COMBATSTATSCOMPONENT_API FRecalculateStatsOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeRecalculateStatsDelegate> BeforeDelegates;

	UPROPERTY()
	TArray<FAfterRecalculateStatsDelegate> AfterDelegates;

public:
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(Before, FBeforeRecalculateStatsDelegate,
		BeforeDelegates, Delegate,
		const EStatEnum, const bool, const float, const float
		);
	
	DECLARE_OUTLET_FUNCTIONS_FourParams(After, FAfterRecalculateStatsDelegate,
		AfterDelegates, Delegate,
		const EStatEnum, const bool, const float, const float
		);
};

#pragma endregion