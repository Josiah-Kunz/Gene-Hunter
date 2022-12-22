#pragma once

/**
 * This tells certain functions which part of the Stat to modify, such as "Current" or "BaseStat".
 */
UENUM(BlueprintType)
enum class EStatValueType : uint8
{
	Current				UMETA(Tooltip="Only modifies current, non-permanent stats (e.g., in battle)."),
	Permanent			UMETA(Tooltip="Only modifies permanent stats, but not current stats."),

	BaseStat			UMETA(Tooltip="Modifies the BaseStat."),
	BasePairs			UMETA(Tooltip="Modifies the BasePairs."),
};
