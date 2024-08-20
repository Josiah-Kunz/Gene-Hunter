#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"
#include "StatRandParams.h"

#include "GetCritMultOutlet.generated.h"

#pragma region Before

class UCombatStatsComponent;
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FBeforeGetCritMultSignature,
                                     float&, BaseMultiplier,
                                     float&, CritBonus,
                                     UCombatStatsComponent*, OwningStats
);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FBeforeGetCritMultDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeGetCritMultSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAfterGetCritMultSignature,
		const float, BaseMultiplier,
		const float, CritBonus,
		UCombatStatsComponent*, OwningStats
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FAfterGetCritMultDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterGetCritMultSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FGetCritMultOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeGetCritMultDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(Before, FBeforeGetCritMultDelegate,
		BeforeDelegates, Delegate,
		float&, 
		float&,
		UCombatStatsComponent*
		);

	UPROPERTY()
	TArray<FAfterGetCritMultDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(After, FAfterGetCritMultDelegate,
		AfterDelegates, Delegate,
			const float, 
			const float,
			UCombatStatsComponent*
		);
};

#pragma endregion