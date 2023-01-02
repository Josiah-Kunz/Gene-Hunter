#pragma once

#include "CoreMinimal.h"

class ComponentUtilities
{

public:

/**
 * Creates and assigns the Component and then adds + registers it to Owner.
 */
#define ADD_COMPONENT(ComponentType, Component, Owner) \
	Component = NewObject< ComponentType >( Owner ); \
	Owner ->AddInstanceComponent( Component ); \
	if ( Component ) \
		Component ->RegisterComponent(); 

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
 *
 * If bTerminal and Component was not found, calls this->DestroyComponent().
 */
	#define SEARCH_FOR_COMPONENT(ComponentType, Component, Owner, bTerminal) \
		if ( Component == nullptr) { \
			Component = Owner ->FindComponentByClass< ComponentType >(); \
			if ( Component == nullptr && bTerminal ) \
				DestroyComponent(); \
		}
	
};
