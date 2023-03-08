#pragma once

#include "CoreMinimal.h"

class ComponentUtilities
{

public:
	
	/**
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
 *
 *	Make sure to do DUMMY_TEST_GC for garbage collection after you're done!
 */
#define DUMMY_TEST_WORLD_AND_ACTOR() \
	UWorld* DummyWorld = UWorld::CreateWorld(EWorldType::Game, false); \
	AActor* DummyActor = DummyWorld->SpawnActor(AActor::StaticClass()); 

/**
 * For unit testing. Creates a:
 *	- UWorld* called DummyWorld
 *	- AActor* called DummyActor
 *	- ComponentType* called ComponentName
 *
 *	Make sure to do DUMMY_TEST_GC for garbage collection after you're done!
 */
#define DUMMY_TEST_COMPONENT(ComponentType, ComponentName) \
	DUMMY_TEST_WORLD_AND_ACTOR(); \
	ComponentType * ComponentName = NewObject<ComponentType>(DummyActor); \
	ComponentName ->RegisterComponent();

/**
 * Destroys the dummy world
 */
#define DUMMY_TEST_GC \
	DummyWorld->DestroyWorld(false);
	
};
