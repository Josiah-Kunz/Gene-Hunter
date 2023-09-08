#pragma once

/**
* Pass these to acquire certain FCombatStat.
 */
UENUM(BlueprintType)
enum class EStatEnum : uint8
{
	Health,
	PhysicalAttack,
	PhysicalDefense,
	SpecialAttack,
	SpecialDefense,
	Haste,
	CriticalHit,
};