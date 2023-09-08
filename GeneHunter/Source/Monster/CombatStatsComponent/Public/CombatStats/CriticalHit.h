// 

#pragma once

#include"CombatStat.h"
#include "CriticalHit.generated.h"

USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FCriticalHit : public FCombatStat
{
	GENERATED_BODY()

	

public:
	inline static constexpr float BaseStatScaling = 3.6e-9;
	inline static constexpr float BaseStatExponent = 4.2f;
	inline static constexpr float LevelScaling = 0.625f;
	
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	virtual float CalculateValue(const uint16 Level) override;

	/**
	 * This Stat's description and such.
	 */
	virtual FSupportingText const SupportingText() const override;
	
	/**
	 * The name of this Stat to be displayed (such as "Physical Attack").
	 */
	virtual FString const Name() const override;

	/**
	 * A shorter version of Name (such as "PhA" for "Physical Attack").
	 */
	virtual FString const Abbreviation() const override;

	/**
	 * The color associated with this Stat.
	 */
	virtual FLinearColor const Color() const override;

protected:

	/**
	 * The critical hit every ten levels. See stats documentation for equations.
	 */
	virtual float SubCrit(const uint16 Level);
	
};
