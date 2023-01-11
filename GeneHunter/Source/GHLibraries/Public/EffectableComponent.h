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
	
public:

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
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_FourParams(BaseName, Param1, Param2, Param3, Param4) \
	DECLARE_DELEGATE_FourParams (F##BaseName##Delegate , Param1, Param2, Param3, Param4);\
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2, Param3 BaseName##P3, Param4 BaseName##P4){ \
	for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 , BaseName##P4 );} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2 , Param3 BaseName##P3 , Param4 BaseName##P4){ \
	for(F##BaseName##Delegate Delegate : After##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 , BaseName##P4 );} 

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_ThreeParams(BaseName, Param1, Param2, Param3) \
	DECLARE_DELEGATE_ThreeParams (F##BaseName##Delegate , Param1, Param2, Param3); \
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2, Param3 BaseName##P3){ \
	for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 );} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2 , Param3 BaseName##P3){ \
	for(F##BaseName##Delegate Delegate : After##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 , BaseName##P3 );} 

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_TwoParams(BaseName, Param1, Param2) \
	DECLARE_DELEGATE_TwoParams (F##BaseName##Delegate , Param1, Param2); \
	void ExecuteBefore##BaseName (Param1 BaseName##P1, Param2 BaseName##P2){ \
	for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 );} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1, Param2 BaseName##P2){ \
	for(F##BaseName##Delegate Delegate : After##BaseName##Array) \
	Delegate.Execute( BaseName##P1, BaseName##P2 );} 

/**
 * Creates two arrays of delegates: Before##BaseName and After##BaseName.
 */
#define EFFECT_DELEGATES_OneParam(BaseName, Param1) \
	DECLARE_DELEGATE_OneParam (F##BaseName##Delegate , Param1);\
	void ExecuteBefore##BaseName (Param1 BaseName##P1){ \
	for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
	Delegate.Execute( BaseName##P1 );} \
	void ExecuteAfter##BaseName (Param1 BaseName##P1){ \
	for(F##BaseName##Delegate Delegate : After##BaseName##Array) \
	Delegate.Execute( BaseName##P1 );} 

/**
 * Creates:
 *	- The delegate type FBaseNameDelegate
 *	- The before/after arrays of delegates: TArray<FBaseNameDelegate> BeforeBaseNameArray
 *	- A function for each before/after to execute the arrays: ExecuteBeforeBaseName (...)
 */
#define EFFECT_DELEGATES(BaseName) \
	DECLARE_DELEGATE (F##BaseName##Delegate );\
	void ExecuteBefore##BaseName (){ \
	for(F##BaseName##Delegate Delegate : Before##BaseName##Array) \
	Delegate.Execute();} \
	void ExecuteAfter##BaseName (){ \
	for(F##BaseName##Delegate Delegate : After##BaseName##Array) \
	Delegate.Execute();} 

#pragma endregion
	
};
