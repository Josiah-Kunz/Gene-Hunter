#pragma once

#include "CombatStatsComponent.h"

struct FStatMod
{
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
	void Modify(UCombatStatsComponent* Stats, const int8 Scale, const bool bPermAndCurrent = false) const;
	
};
