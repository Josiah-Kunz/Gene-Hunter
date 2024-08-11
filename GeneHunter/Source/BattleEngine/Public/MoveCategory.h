#pragma once

UENUM(BlueprintType, meta=(Bitflags))
enum class EMoveCategory : uint8
{
	None		UMETA(Tooltip="Default. Don't use this. If you see it, it's an error."),
	Physical	UMETA(Tooltip="If damaging, the Move relies on the user's physical abilities, like strength. If status, the target is physically afflicted."),
	Special		UMETA(Tooltip="If damaging, the Move relies on the user's non-physical abilities, like psychic or spiritual ability. If status, the target is non-physically afflicted."),
	Healing		UMETA(Tooltip="A move that restores health (self, allies, enemies, etc.)."),
	Summoning	UMETA(Tooltip="A move that summons an object or creature."),
	Utility		UMETA(Tooltip="Does nothing to opponent or self (does not even attach a status effect like Pokemon's Disable). Pokemon example: Pay Day (but without damage)"),
};

ENUM_CLASS_FLAGS(EMoveCategory)