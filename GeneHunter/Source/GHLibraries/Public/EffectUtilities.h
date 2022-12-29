#pragma once

#include "CoreMinimal.h"

class EffectUtilities
{

public:

#define REQUIRE_COMPONENT(ComponentType, Component, Owner) \
	if ( Component == nullptr) { \
		Component = Owner ->FindComponentByClass< ComponentType >(); \
		if ( Component == nullptr) \
			Component = NewObject< ComponentType >( Owner ); \
	}
	
};
