#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "PositiveAuraComponent.h"
#include "Outlets/ModifyStatOutlet.h"
#include "FullBloom.generated.h"

/**
 * +20% max health
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class POSITIVEAURACOMPONENT_API UFullBloom : public UPositiveAuraComponent
{
	GENERATED_BODY()

	UFullBloom();
	
	
};

