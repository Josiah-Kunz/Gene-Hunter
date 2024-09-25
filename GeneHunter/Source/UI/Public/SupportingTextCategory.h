#pragma once

/**
* Represents the kind of SupportingText FText (e.g., Description).
 */
UENUM(BlueprintType, meta=(Bitflags))
enum class ESupportingTextCategory : uint8
{
	None,
	DevNote,
	Summary,
	Description,
	FlavorText,
};

ENUM_CLASS_FLAGS(ESupportingTextCategory)