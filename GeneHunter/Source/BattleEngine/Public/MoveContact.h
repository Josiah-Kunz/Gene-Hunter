#pragma once

UENUM(BlueprintType, meta=(Bitflags))
enum class EMoveContact : uint8
{
	None				UMETA(Tooltip="No contact (e.g., Summoning)."),
	PhysicalContact		UMETA(Tooltip="The damage or status requires the user to make physical contact with the target."),
	SpecialContact		UMETA(Tooltip="The damage or status does not require the user to make physical contact with the target."),
};

ENUM_CLASS_FLAGS(EMoveContact)