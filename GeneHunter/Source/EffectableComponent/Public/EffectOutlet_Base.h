#pragma once

#include "EffectOutlet_Base.generated.h"

/**
 * An enum to help determine where a delegate triggers.
 *	- If Before, small priorities trigger first (1, 2, 3, ...)
 *	- If After, large priorities trigger first (999, 998, ...)
 */
UENUM(BlueprintType)
enum class EDelegateTriggerTiming : uint8
{
	Before,
	After,
};

/**
 * Base struct for effect "outlets" (see documentation). Note that inherited structs need to:
 *	- Implement a DECLARE_DYNAMIC_DELEGATE_xParams macro for a delegate signature
 *	- Declare the delegate via, e.g.,:
 *		public:
 *			UPROPERTY()
 *			FDelegateSignature Delegate;
 */
USTRUCT(Blueprintable)
struct EFFECTABLECOMPONENT_API FEffectOutlet_Base
{
	GENERATED_BODY()

public:

	/**
	 * Helpful tool when placing delegates into their arrays based on priority. See also UEffectComponent::GetPriority.
	 *
	 * For example, if TargetPriority > ComparisonPriority and EDelegateTriggerTiming::Before, returns true.
	 */
	static bool IsPriorityLowerIndex(const float TargetPriority, const float ComparisonPriority,
		const EDelegateTriggerTiming BeforeOrAfter)
	{
		switch(BeforeOrAfter)
		{
		case EDelegateTriggerTiming::Before:
			return TargetPriority > ComparisonPriority;
		case EDelegateTriggerTiming::After:
			return TargetPriority < ComparisonPriority;
		}

		UE_LOG(LogTemp, Error, TEXT("Unknown  Before or After option: %s in %s::IsPriorityLowerIndex() !"),
				*(UEnum::GetValueAsName(BeforeOrAfter).ToString()),
				*FString(FEffectOutlet_Base::StaticStruct()->GetName())
				);
		return false;
	}
	
/** Creates Add(), which inserts a Delegate to the DelegateArray based on its priority. */
#define DECLARE_ADD_FUNCTION(BeforeOrAfter, DelegateType, DelegateArray) \
public: \
	void Add##BeforeOrAfter(const DelegateType NewDelegate) \
	{ \
		bool bAdded = false; \
		for(int i=0; i< DelegateArray##.Num(); i++) \
		{ \
			if (IsPriorityLowerIndex(NewDelegate.Priority, DelegateArray##[i].Priority, EDelegateTriggerTiming::##BeforeOrAfter)) \
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

/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the DelegateArray
 *	- Add, which adds a Delegate to the DelegateArray
 */
#define DECLARE_OUTLET_FUNCTIONS_OneParam(BeforeOrAfter, DelegateType, DelegateArray, DelegateVariable, Param1Type) \
public: \
	void Execute##BeforeOrAfter##( Param1Type DelegateArray##__P1) \
	{ \
		for ( DelegateType##& Delegate : DelegateArray ) \
		{ \
			if (!Delegate.##DelegateVariable##.ExecuteIfBound( DelegateArray##__P1 ))\
			{ \
				UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
	\
	DECLARE_ADD_FUNCTION( BeforeOrAfter , DelegateType, DelegateArray);
	

/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the array
 *	- Add, which adds a Delegate to the array
 */
#define DECLARE_OUTLET_FUNCTIONS_TwoParams(BeforeOrAfter, DelegateType, DelegateArray, DelegateVariable, Param1Type, Param2Type) \
public: \
	void Execute##BeforeOrAfter##( Param1Type DelegateArray##__P1, Param2Type DelegateArray##__P2) \
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
	DECLARE_ADD_FUNCTION( BeforeOrAfter , DelegateType, DelegateArray);
	
/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the array
 *	- Add, which adds a Delegate to the array
 */
#define DECLARE_OUTLET_FUNCTIONS_ThreeParams(BeforeOrAfter, DelegateType, DelegateArray, DelegateVariable, Param1Type, Param2Type, Param3Type) \
public: \
	void Execute##BeforeOrAfter##( Param1Type DelegateArray##__P1, Param2Type DelegateArray##__P2, Param3Type DelegateArray##__P3) \
	{ \
		for ( DelegateType##& Delegate : DelegateArray ) \
		{ \
		if (!Delegate.##DelegateVariable##.ExecuteIfBound( DelegateArray##__P1, DelegateArray##__P2, DelegateArray##__P3 ))\
			{ \
			UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
	\
	DECLARE_ADD_FUNCTION( BeforeOrAfter , DelegateType, DelegateArray);

/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the array
 *	- Add, which adds a Delegate to the array
 */
#define DECLARE_OUTLET_FUNCTIONS_FourParams(BeforeOrAfter, DelegateType, DelegateArray, DelegateVariable, Param1Type, Param2Type, Param3Type, Param4Type) \
public: \
	void Execute##BeforeOrAfter##( Param1Type DelegateArray##__P1, Param2Type DelegateArray##__P2, Param3Type DelegateArray##__P3, Param4Type DelegateArray##__P4) \
	{ \
		for ( DelegateType##& Delegate : DelegateArray ) \
		{ \
		if (!Delegate.##DelegateVariable##.ExecuteIfBound( DelegateArray##__P1, DelegateArray##__P2, DelegateArray##__P3, DelegateArray##__P4 ))\
			{ \
			UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
	\
	DECLARE_ADD_FUNCTION( ##BeforeOrAfter , DelegateType, DelegateArray);

/**
 * Creates two functions:
 *	- Execute, which called ExecuteIfBound on every Delegate in the array
 *	- Add, which adds a Delegate to the array
 */
#define DECLARE_OUTLET_FUNCTIONS_FiveParams(BeforeOrAfter, DelegateType, DelegateArray, DelegateVariable, Param1Type, Param2Type, Param3Type, Param4Type, Param5Type) \
public: \
	void Execute##BeforeOrAfter##( Param1Type DelegateArray##__P1, Param2Type DelegateArray##__P2, Param3Type DelegateArray##__P3, Param4Type DelegateArray##__P4, Param5Type DelegateArray##__P5) \
	{ \
		for ( DelegateType##& Delegate : DelegateArray ) \
		{ \
		if (!Delegate.##DelegateVariable##.ExecuteIfBound( DelegateArray##__P1, DelegateArray##__P2, DelegateArray##__P3, DelegateArray##__P4 , DelegateArray##__P5 ))\
			{ \
			UE_LOG(LogTemp, Warning, TEXT("Outlet no longer bound! Surely this is an error.")); \
			} \
		} \
	} \
	\
	DECLARE_ADD_FUNCTION( ##BeforeOrAfter , DelegateType, DelegateArray);

};