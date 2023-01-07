#pragma once

/**
* Pass these to acquire certain FStats.
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