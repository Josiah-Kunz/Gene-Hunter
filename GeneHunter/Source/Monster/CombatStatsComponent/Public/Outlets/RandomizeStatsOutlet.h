#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"
#include "StatRandParams.h"

#include "RandomizeStatsOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FBeforeRandomizeStatsSignature,
	const EStatEnum, TargetStat,
	const FStatRandParams, OriginalParams,
	FStatRandParams&, AttemptedParams
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FBeforeRandomizeStatsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeRandomizeStatsSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAfterRandomizeStatsSignature,
	const EStatEnum, TargetStat,
	const FStatRandParams, OriginalParams,
	const FStatRandParams, UsedParams
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FAfterRandomizeStatsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterRandomizeStatsSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FRandomizeStatsOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeRandomizeStatsDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(Before, FBeforeRandomizeStatsDelegate,
		BeforeDelegates, Delegate,
		const EStatEnum, const FStatRandParams, FStatRandParams&
		);

	UPROPERTY()
	TArray<FAfterRandomizeStatsDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(After, FAfterRandomizeStatsDelegate,
		AfterDelegates, Delegate,
		const EStatEnum, const FStatRandParams, const FStatRandParams
		);
};

#pragma endregion