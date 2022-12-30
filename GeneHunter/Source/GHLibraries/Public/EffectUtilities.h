#pragma once

#include "CoreMinimal.h"

class EffectUtilities
{

public:

/**
 * Searches Owner for the ComponentType. If one is found, it is assigned as Component. Otherwise, a new one is created,
 *	added to Owner, and registered.
 */
#define REQUIRE_COMPONENT(ComponentType, Component, Owner) \
	if ( Component == nullptr) { \
		Component = Owner ->FindComponentByClass< ComponentType >(); \
		if ( Component == nullptr){ \
			Component = NewObject< ComponentType >( Owner ); \
			Owner ->AddInstanceComponent( Component ); \
			Component ->RegisterComponent(); \
		} \
	}
	
};
