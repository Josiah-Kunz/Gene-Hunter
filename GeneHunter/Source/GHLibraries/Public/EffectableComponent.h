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

#pragma region Effect delegate macros
	
/**
 * Same as DECLARE_DELEGATE_FourParams but with the naming convention FBaseNameDelegate.
 */
#define EFFECT_DELEGATES_FourParams(BaseName, Param1, Param2, Param3, Param4) \
	DECLARE_DELEGATE_FourParams (F##BaseName##Delegate , Param1, Param2, Param3, Param4);

/**
 * Same as DECLARE_DELEGATE_ThreeParams but with the naming convention FBaseNameDelegate.
 */
#define EFFECT_DELEGATES_ThreeParams(BaseName, Param1, Param2, Param3) \
	DECLARE_DELEGATE_ThreeParams (F##BaseName##Delegate , Param1, Param2, Param3); 

/**
 * Same as DECLARE_DELEGATE_TwoParams but with the naming convention FBaseNameDelegate.
 */
#define EFFECT_DELEGATES_TwoParams(BaseName, Param1, Param2) \
	DECLARE_DELEGATE_TwoParams (F##BaseName##Delegate , Param1, Param2);

/**
 * Same as DECLARE_DELEGATE_OneParams but with the naming convention FBaseNameDelegate.
 */
#define EFFECT_DELEGATES_OneParam(BaseName, Param1) \
	DECLARE_DELEGATE_OneParam (F##BaseName##Delegate , Param1);

/**
 * Same as DECLARE_DELEGATE but with the naming convention FBaseNameDelegate.
 */
#define EFFECT_DELEGATES(BaseName) \
	DECLARE_DELEGATE (F##BaseName##Delegate );
	
public:

/**
 * Declares the array itself. Must be declared after the EFFECT_DELEGATES_params macro.
 *
 * Don't forget to do the UPROPERTY before you declare this macro:
 * 
 *	public:
 *		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delegate Arrays")
 *
 *	(the macro itself cannot do it since you can't wrap UMacros inside C++ macros)
 */
#define EFFECT_DELEGATE_BEFORE_ARRAY(BaseName) \
	TArray<F##BaseName##Delegate> Before##BaseName##Array ;

/**
 * Declares the array itself. Must be declared after the EFFECT_DELEGATES_PARAMS macro.
 *
 * Don't forget to do the UPROPERTY before you declare this macro:
 * 
 *	public:
 *		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Delegate Arrays")
 *
 *	(the macro itself cannot do it since you can't wrap UMacros inside C++ macros)
 */
#define EFFECT_DELEGATE_AFTER_ARRAY(BaseName) \
	TArray<F##BaseName##Delegate> After##BaseName##Array ;
	
/**
 * Creates two functions to provide code execution: ExecuteBefore##BaseName and ExecuteAfter##BaseName. These functions
 *	loop through the delegate arrays and call execute.
 */
#define EFFECT_FUNCTIONS_FourParams(BaseName, Param1, Param2, Param3, Param4) \
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2, Param3 BaseName##P3, Param4 BaseName##P4) \
	{ \
		for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
		{ \
			Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 , BaseName##P4 ); \
		} \
	} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2 , Param3 BaseName##P3 , Param4 BaseName##P4) \
	{ \
		for(F##BaseName##Delegate Delegate : After##BaseName##Array) { \
			Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 , BaseName##P4 ); \
		} \
	}
	

/**
 * Creates two functions to provide code execution: ExecuteBefore##BaseName and ExecuteAfter##BaseName. These functions
 *	loop through the delegate arrays and call execute.
 */
#define EFFECT_FUNCTIONS_ThreeParams(BaseName, Param1, Param2, Param3) \
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2, Param3 BaseName##P3 ) \
	{ \
		for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
		{ \
			Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 ); \
		} \
	} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2 , Param3 BaseName##P3) \
	{ \
		for(F##BaseName##Delegate Delegate : After##BaseName##Array) { \
			Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 ); \
		} \
	}

/**
 * Creates two functions to provide code execution: ExecuteBefore##BaseName and ExecuteAfter##BaseName. These functions
 *	loop through the delegate arrays and call execute.
 */
#define EFFECT_FUNCTIONS_TwoParams(BaseName, Param1, Param2) \
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2) \
	{ \
		for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
		{ \
			Delegate.Execute( BaseName##P1, BaseName##P2 ); \
		} \
	} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2 ) \
	{ \
		for(F##BaseName##Delegate Delegate : After##BaseName##Array) { \
			Delegate.Execute( BaseName##P1, BaseName##P2 ); \
		} \
	}

/**
 * Creates two functions to provide code execution: ExecuteBefore##BaseName and ExecuteAfter##BaseName. These functions
 *	loop through the delegate arrays and call execute.
 */
#define EFFECT_FUNCTIONS_OneParam(BaseName, Param1) \
	void ExecuteBefore##BaseName (Param1 BaseName##P1) \
	{ \
		for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
		{ \
			Delegate.Execute( BaseName##P1); \
		} \
	} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1) \
	{ \
		for(F##BaseName##Delegate Delegate : After##BaseName##Array) { \
			Delegate.Execute( BaseName##P1 ); \
		} \
	}

/**
 * Creates two functions to provide code execution: ExecuteBefore##BaseName and ExecuteAfter##BaseName. These functions
 *	loop through the delegate arrays and call execute.
 */
#define EFFECT_FUNCTIONS(BaseName) \
	void ExecuteBefore##BaseName () \
	{ \
		for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
		{ \
			Delegate.Execute(); \
		} \
	} \
	void ExecuteAfter##BaseName () \
	{ \
		for(F##BaseName##Delegate Delegate : After##BaseName##Array) { \
			Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 , BaseName##P4 ); \
		} \
	}


#pragma endregion
	
};
