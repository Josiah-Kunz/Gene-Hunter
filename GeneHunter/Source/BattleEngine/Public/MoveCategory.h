#pragma once

UENUM(BlueprintType, meta=(Bitflags))
enum class EMoveCategory : uint8
{
	None			UMETA(Tooltip="Default. Don't use this. If you see it, it's an error."),
	PhysicalDamage	UMETA(Tooltip="If damaging, the Move relies on the user's physical abilities, like strength."),
	SpecialDamage	UMETA(Tooltip="If damaging, the Move relies on the user's non-physical abilities, like psychic or spiritual ability."),
	PhysicalHealing	UMETA(Tooltip="A move that restores health (self, allies, enemies, etc.) by physical means. For example, an injection, food, a bandage, or acupuncture."),
	SpecialHealing	UMETA(Tooltip="A move that restores health (self, allies, enemies, etc.) non-physically. For example, mental healing, emotional support, spiritual peace, or the reversing of time to heal wounds."),
	Summoning		UMETA(Tooltip="A move that summons an object or creature."),
	Utility			UMETA(Tooltip="Does no damage to opponent or self. May still attach effects. Pokemon example: Thunder Wave or Pay Day (but without damage)"),
};

ENUM_CLASS_FLAGS(EMoveCategory)