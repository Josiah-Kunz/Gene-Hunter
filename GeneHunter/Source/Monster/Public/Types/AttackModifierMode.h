#pragma once

/*
* Note: this is an interesting phenomenon also seen in statistical thermodynamics and has to do with a binomial
 *	expansion. MultiType has higher highs (hits select things much harder) and lower lows (is more easily resisted)
 *	compared to Coverage.
 */
UENUM(BlueprintType)
enum class EAttackModifierMode : uint8
{
	MultiType		UMETA(DisplayName = "Multi-Type", Tooltip="Takes the Types in the array as a single, multi-Typed attack."),
	Coverage		UMETA(DisplayName = "Coverage", Tooltip="Takes the Types in the array as separate, singly-Typed attacks."),
};