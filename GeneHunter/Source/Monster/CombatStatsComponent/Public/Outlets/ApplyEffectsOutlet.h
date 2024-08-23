#pragma once
#include "EffectDelegate.h"
#include "EffectOutlet.h"
#include "MoveData.h"

#include "ApplyEffectsOutlet.generated.h"

#pragma region Before

class UCombatStatsComponent;
DECLARE_DYNAMIC_DELEGATE_FiveParams(FBeforeApplyEffectsSignature,
                                     uint16&, NumStacks,
                                     bool&, bMutual,
                                     UMoveData*, MoveData,
									 UCombatStatsComponent*, Attacker,
                                     UCombatStatsComponent*, OwningStats
);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FBeforeApplyEffectsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeApplyEffectsSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_FiveParams(FAfterApplyEffectsSignature,
		const uint16, NumStacks,
		const bool, bMutual,
		UMoveData*, MoveData,
		UCombatStatsComponent*, Attacker,
		UCombatStatsComponent*, OwningStats
	);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FAfterApplyEffectsDelegate : public FEffectDelegate
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterApplyEffectsSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FApplyEffectsOutlet : public FEffectOutlet
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeApplyEffectsDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FiveParams(Before, FBeforeApplyEffectsDelegate, BeforeDelegates, Delegate,
		uint16&,
		bool&,
		UMoveData*,
		UCombatStatsComponent*,
		UCombatStatsComponent*
		);

	UPROPERTY()
	TArray<FAfterApplyEffectsDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_FiveParams(After, FAfterApplyEffectsDelegate, AfterDelegates, Delegate,
		const uint16,
		const bool,
		UMoveData*,
		UCombatStatsComponent*,
		UCombatStatsComponent*
		);
};

#pragma endregion