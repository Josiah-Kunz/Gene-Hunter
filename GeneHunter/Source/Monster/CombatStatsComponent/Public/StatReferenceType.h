#pragma once

/**
 * When modifying a Stat, this tells it what value to use. For example, if you're trying to add 50%, this answers the
 * question "50% of what? My own value, like Current, or another value, like Permanent?"
 */
UENUM(BlueprintType)
enum class EStatReferenceType : uint8
{
	Self			UMETA(Tooltip="Use your own value as the reference value."),
	Current			UMETA(Tooltip="Use the Current value of the Stat as reference."),
	Permanent		UMETA(Tooltip="Use the Permanent value of the Stat as reference."),

	SpecifiedValue	UMETA(Tooltip="Use another, custom value as reference."),
};
