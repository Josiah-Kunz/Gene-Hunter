#pragma once

/**
* Represents the result of a Purge attempt in, e.g., UEffectComponent::Purge.
 */
UENUM(BlueprintType, meta=(Bitflags))
enum class EStackChangeResult : uint8
{
	None,
	Purged,
	StacksReduced,
	StacksIncreased,
};

ENUM_CLASS_FLAGS(EStackChangeResult)