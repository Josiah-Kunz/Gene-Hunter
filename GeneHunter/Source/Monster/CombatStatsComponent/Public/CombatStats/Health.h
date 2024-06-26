// 

#pragma once

#include"CombatStat.h"
#include "Health.generated.h"

/**
 * 
 */
USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FHealth : public FCombatStat
{
	GENERATED_BODY()

public:
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
	
};
