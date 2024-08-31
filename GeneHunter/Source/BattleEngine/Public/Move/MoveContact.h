#pragma once

UENUM(BlueprintType, meta=(Bitflags))
enum class EMoveContact : uint8
{
	None				UMETA(Tooltip="No contact (e.g., Summoning or damaging from afar)."),
	PhysicalContact		UMETA(Tooltip="The damage or status requires the user to make physical contact with the target. Example: punching something."),
	SpecialContact		UMETA(Tooltip="The damage or status requires the user to make non-physical contact with the target. Example: direct psychic connection."),
};

ENUM_CLASS_FLAGS(EMoveContact)