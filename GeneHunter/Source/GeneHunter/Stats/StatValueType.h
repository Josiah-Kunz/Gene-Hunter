#pragma once

UENUM(BlueprintType)
enum class EStatValueType : uint8
{
	Current			UMETA(Tooltip="Only adds to current, non-permanent stats (e.g., in battle)."),
	Permanent		UMETA(Tooltip="Only adds to permanent stats, but not current stats."),
	CurrentAndPermanent	UMETA(Tooltip="Adds to both current and permanent stats (e.g., on level gain). Note: modifies permanent first.")
};
