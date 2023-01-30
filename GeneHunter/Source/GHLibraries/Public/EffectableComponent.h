#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EffectableComponent.generated.h"

/**
 * The base class for so-called "effectable" components, which can house effects. Example: UStatsComponent should
 *	inherit from this, as you can create effects that "plug in" to UStatsComponent.
 */
UCLASS()
class GHLIBRARIES_API UEffectableComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/**
	 * Priority for "intrinsic" delegates. These delegates are defined in C# and hence don't have an EffectComponent.
	 * An example is UStatsComponent::UpdateStatsAfterLevel. This should always happen regardless of, e.g., buffs.
	 */
	inline static constexpr float IntrinsicPriority = 999999999;

#define DECLARE_AFTER_OUTLET_FUNCTIONS_TwoParams(OutletStructName, OutletPropertyName, OutletDelegateName, Param1Type, Param2Type) \
	private: \
	void ExecuteAfter##OutletPropertyName##( Param1Type OutletPropertyName##__P1, Param2Type OutletPropertyName##__P2) \
	{ \
		OutletPropertyName##.ValueSort([](const float PriorityA, const float PriorityB) \
		{ \
			return PriorityA < PriorityB; \
		}); \
		for(TPair< OutletStructName , float> Pair : &##OutletPropertyName ) \
		{ \
			if (!Pair.Key.##OutletDelegateName##.ExecuteIfBound( OutletPropertyName##__P1, OutletPropertyName##__P2 ))\
			{ \
				UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
	\
	public: \
	void Add##OutletPropertyName##(const OutletStructName Outlet, const float Priority) \
	{ \
		OutletPropertyName##.Add(Outlet, Priority); \
	}
	
};
