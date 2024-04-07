#pragma once

#include "CombatStatsComponent.h"
#include "StatMod.generated.h"

USTRUCT(Blueprintable)
struct EFFECTCOMPONENT_API FStatMod
{

	GENERATED_BODY()
	
public:

	EStatEnum Stat;
	float Modification;
	EModificationMode Mode;
	EStatValueType ValueType;

	/**
	 * Modifies the stat according to how this effect should work.
	 *
	 * @param Scale If modifying the stat, this should be 1. If un-modifying, this should be -1.
	 */
	void Modify(UCombatStatsComponent* Stats, const bool bIncrease, const bool bPermAndCurrent = false) const;
	
};
