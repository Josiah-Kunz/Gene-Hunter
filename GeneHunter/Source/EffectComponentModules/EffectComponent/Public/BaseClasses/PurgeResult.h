#pragma once

/**
* Represents the result of a Purge attempt in, e.g., UEffectComponent::Purge.
 */
UENUM(BlueprintType, meta=(Bitflags))
enum class EPurgeResult : uint8
{
	None,
	Purged,
	StacksReduced,
};