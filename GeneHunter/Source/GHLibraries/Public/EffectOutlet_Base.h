#pragma once

#include "EffectOutlet_Base.generated.h"

/**
 * Base struct for effect "outlets" (see documentation). Note that inherited structs need to:
 *	- Implement a DECLARE_DYNAMIC_DELEGATE_xParams macro for a delegate signature
 *	- Declare the delegate via, e.g.,:
 *		public:
 *			UPROPERTY()
 *			FDelegateSignature Delegate;
 */
USTRUCT(Blueprintable)
struct GHLIBRARIES_API FEffectOutlet_Base
{
	GENERATED_BODY()

public:

	/** Affects effect execution order (see UEffectComponent::GetPriority). */
	float Priority = 50;

#define DECLARE_AFTER_OUTLET_FUNCTIONS_TwoParams(OutletStructName, OutletTArrayName, OutletDelegateName, Param1Type, Param2Type) \
private: \
	void Execute##OutletTArrayName##( Param1Type OutletTArrayName##__P1, Param2Type OutletTArrayName##__P2) \
	{ \
		for ( OutletStructName##& Outlet : OutletTArrayName ) \
		{ \
			if (!Outlet.##OutletDelegateName##.ExecuteIfBound( OutletTArrayName##__P1, OutletTArrayName##__P2 ))\
			{ \
				UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
\
public: \
	void Add##OutletTArrayName##(const OutletStructName NewOutlet) \
	{ \
		bool bAdded = false; \
		for(int i=0; i< OutletTArrayName##.Num(); i++) \
		{ \
			if (NewOutlet.Priority < OutletTArrayName##[i].Priority) \
			{ \
				OutletTArrayName##.Insert(NewOutlet, i); \
				bAdded = true; \
			} \
		} \
		if (!bAdded) \
		{ \
			OutletTArrayName##.Add(NewOutlet); \
		} \
	}
	
};
