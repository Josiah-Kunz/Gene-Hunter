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

/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the array
 *	- Add, which adds a Delegate to the array
 */
#define DECLARE_AFTER_OUTLET_FUNCTIONS_TwoParams(DelegateType, DelegateArray, DelegateVariable, Param1Type, Param2Type) \
public: \
	void Execute( Param1Type DelegateArray##__P1, Param2Type DelegateArray##__P2) \
	{ \
		for ( DelegateType##& Delegate : DelegateArray ) \
		{ \
			if (!Delegate.##DelegateVariable##.ExecuteIfBound( DelegateArray##__P1, DelegateArray##__P2 ))\
			{ \
				UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
\
	void Add(const DelegateType NewDelegate) \
	{ \
		bool bAdded = false; \
		for(int i=0; i< DelegateArray##.Num(); i++) \
		{ \
			if (NewDelegate.Priority < DelegateArray##[i].Priority) \
			{ \
				DelegateArray##.Insert(NewDelegate, i); \
				bAdded = true; \
			} \
		} \
		if (!bAdded) \
		{ \
			DelegateArray##.Add(NewDelegate); \
		} \
	}
	
};
