#pragma once

UENUM(BlueprintType)
enum class EModificationMode : uint8
{
	AddAbsolute			UMETA(Tooltip="E.g., | 100 & 1.5 => 100 + 1.5 => 101.5 | 100 & -10 => 100 - 10 => 90 |"),
	AddFraction			UMETA(Tooltip="E.g., | 100 & 1.5 => 100 + 150 => 250 | 100 & 0.5 => 100 + 50 => 150 |"),
	AddPercentage		UMETA(Tooltip="E.g., | 200 & 1.5 => 200 + 200*1.5% => 203 | 30 & 50 => 30 + 30*50% => 45 |"),

	MultiplyAbsolute	UMETA(Tooltip="E.g., | 100 & 1.5 => 100 * 1.5 => 150 | 100 & -10 => 100 * -10 => -1000 |"),
	MultiplyPercentage	UMETA(Tooltip="E.g., | 200 & 1.5 => 200 * 1.5% => 3 | 30 & 50 => 30 * 50% => 15 |"),
};
