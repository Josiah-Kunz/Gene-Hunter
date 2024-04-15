#pragma once

#include "CoreMinimal.h"
#include "MathUtil.h"
#include "Net/NUTUtilNet.h"

class ComponentUtilities
{

public:

	static float GetTolerance(const float Current, const float Expected, const float TolPercent = 1)
	{
		return TolPercent/100 * (Current + Expected)/2;
	}

	static float AreTheSame(const float F1, const float F2, const float TolPercent = 1)
	{
		return FMathf::Abs(F1-F2) < GetTolerance(F1, F2, TolPercent);
	}
	
	/**
	 * For unit testing. Creates a:
	 *	- UWorld* called DummyWorld
	 *	- AActor* called DummyActor
	 *
	 *	Make sure to do ComponentUtilities::DestroyDummyWorld(DummyWorld); for garbage collection after you're done!
	 */
	static void DummyTestWorldAndActor(UWorld*& DummyWorld, AActor*& DummyActor)
	{
		DummyWorld = NUTNet::CreateUnitTestWorld(true); 
		DummyActor = DummyWorld->SpawnActor(AActor::StaticClass());
	};

	/**
	 * Destroys the dummy world
	 */
	static void DestroyDummyWorld(UWorld* World)
	{

		World->DestroyWorld(true);
		
		/*
		 * Note: I'm sincerely not sure why we get the error "unresolved external symbol" about
		 *	NUTNet::CleanupUnitTestWorlds. Maybe it's marked as internal-only? I'll just hope garbage collection
		 *	happens on its own during a unit test I guess =(
		 */

		//NUTNet::MarkUnitTestWorldForCleanup(World, true);
		//NUTNet::CleanupUnitTestWorlds();
	}
	
	/*
	 * Note: The following must be macros to be generic enough. Otherwise, we'd have to #include all component.h for the
	 *	functions to work.
	 */

/**
 * Creates a new variable as the Component and then adds + registers it to Owner.
 */
#define ADD_NEW_COMPONENT(ComponentType, NewVariableName, Owner) \
	ComponentType * NewVariableName; \
	ADD_COMPONENT( ComponentType, NewVariableName, Owner)

/**
 * Creates and assigns the Component from an existing variable and then adds + registers it to Owner.
 */
#define ADD_COMPONENT(ComponentType, Component, Owner) \
	Component = NewObject< ComponentType >( Owner ); \
	if ( Component ){ \
		Owner ->AddInstanceComponent( Component ); \
		Component ->RegisterComponent(); \
	}

/**
 * If the input Component is null, searches Owner for the ComponentType. If one is found, it is assigned as Component.
 *	Otherwise, a new one is created, added to Owner, and registered.
 *
 * If not null, attaches it to the Owner and registers it.
 */
#define REQUIRE_COMPONENT(ComponentType, Component, Owner) \
	if ( Component == nullptr) { \
		Component = Owner ->FindComponentByClass< ComponentType >(); \
		if ( Component == nullptr){ \
			ADD_COMPONENT( ComponentType , Component , Owner ) \
		} \
	} else { \
		Owner ->AddInstanceComponent( Component ); \
		Component ->RegisterComponent(); \
	}

/**
 * If the input Component is null, searches Owner for the ComponentType. If one is found, it is assigned as Component.
 */
#define SEARCH_FOR_COMPONENT(ComponentType, Component, Owner) \
	if ( Component == nullptr) { \
		Component = Owner ->FindComponentByClass< ComponentType >(); \
	}
	
/**
 * If the input Component is null, searches Owner for the ComponentType. If one is found, it is assigned as Component.
 *
 * If bTerminal and Component was not found, calls this->DestroyComponent().
 */
#define SEARCH_FOR_COMPONENT_OR_DESTROY(ComponentType, Component, Owner, bTerminal) \
	SEARCH_FOR_COMPONENT(ComponentType, Component, Owner); \
	if ( Component == nullptr && bTerminal ) \
	{ \
		DestroyComponent(); \
	}

/**
 * For unit testing. Creates a:
 *	- UWorld* called DummyWorld
 *	- AActor* called DummyActor
 *	- ComponentType* called ComponentName
 *
 *	Make sure to do ComponentUtilities::DestroyDummyWorld(DummyWorld); for garbage collection after you're done!
 */
#define DUMMY_TEST_COMPONENT(ComponentType, ComponentName) \
	UWorld* DummyWorld; AActor* DummyActor; \
	ComponentUtilities::DummyTestWorldAndActor(DummyWorld, DummyActor); \
	ComponentType * ComponentName = NewObject<ComponentType>(DummyActor); \
	ComponentName ->RegisterComponent();
	
};
