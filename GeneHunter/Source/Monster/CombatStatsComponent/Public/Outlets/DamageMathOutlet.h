#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"

#include "DamageMathOutlet.generated.h"

#pragma region Before

class UCombatStatsComponent;
DECLARE_DYNAMIC_DELEGATE_SevenParams(FBeforeDamageMathSignature,
                                     float&, BasePower,
                                     float&, CritMultiplier,
                                     float&, RandFluct,
									 float&, Stab,
									 float&, TypeAdvantage,
									 UCombatStatsComponent*, Attacker,
                                     UCombatStatsComponent*, OwningStats
);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FBeforeDamageMathDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeDamageMathSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_SevenParams(FAfterDamageMathSignature,
		const float, BasePower,
		const float, CritMultiplier,
		const float, RandFluct,
		const float, Stab,
		const float, TypeAdvantage,
		UCombatStatsComponent*, Attacker,
		UCombatStatsComponent*, OwningStats
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FAfterDamageMathDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterDamageMathSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FDamageMathOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeDamageMathDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_SevenParams(Before, FBeforeDamageMathDelegate,
		BeforeDelegates, Delegate,
		float&,
		float&,
		float&,
		float&,
		float&,
		UCombatStatsComponent*,
		UCombatStatsComponent*
		);

	UPROPERTY()
	TArray<FAfterDamageMathDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_SevenParams(After, FAfterDamageMathDelegate,
		AfterDelegates, Delegate,
		const float,
		const float,
		const float,
		const float,
		const float,
		UCombatStatsComponent*,
		UCombatStatsComponent*
		);
};

#pragma endregion