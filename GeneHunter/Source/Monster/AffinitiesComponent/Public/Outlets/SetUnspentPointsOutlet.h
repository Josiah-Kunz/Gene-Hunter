#pragma once
#include "EffectDelegate_Base.h"
#include "EffectOutlet_Base.h"

#include "SetUnspentPointsOutlet.generated.h"

#pragma region Before

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FBeforeSetUnspentPointsSignature,
	const uint8, OriginalPoints,
	const uint8, OriginalInput,
	uint8&, SetPoints);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FBeforeSetUnspentPointsDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FBeforeSetUnspentPointsSignature Delegate;
	
};

#pragma endregion

#pragma region After

DECLARE_DYNAMIC_DELEGATE_ThreeParams(FAfterSetUnspentPointsSignature,
	const uint8, OriginalPoints,
	const uint8, OriginalInput,
	const uint8, SetPoints);

/**
 * Since delegates can't fit in TArrays, we need to wrap them in something.
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FAfterSetUnspentPointsDelegate : public FEffectDelegate_Base
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FAfterSetUnspentPointsSignature Delegate;
	
};

#pragma endregion

#pragma region Outlet

/**
 * 
 */
USTRUCT(Blueprintable)
struct AFFINITIESCOMPONENT_API FSetUnspentPointsOutlet : public FEffectOutlet_Base
{
	GENERATED_BODY()

private:
	
	UPROPERTY()
	TArray<FBeforeSetUnspentPointsDelegate> BeforeDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(Before, FBeforeSetUnspentPointsDelegate,
		BeforeDelegates, Delegate, const uint8, const uint8, uint8&);

	UPROPERTY()
	TArray<FAfterSetUnspentPointsDelegate> AfterDelegates;
	
	DECLARE_OUTLET_FUNCTIONS_ThreeParams(After, FAfterSetUnspentPointsDelegate,
		AfterDelegates, Delegate, const uint8, const uint8, const uint8);
};

#pragma endregion