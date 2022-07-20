// 

#pragma once

#include "GeneHunter/Stats/Stat.h"
#include "CriticalHit.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UCriticalHit : public UStat
{
	GENERATED_BODY()

	

public:

	const float BaseStatScaling = 3.6e-9;
	const float BaseStatExponent = 4.2f;
	const float LevelScaling = 0.625f;
	
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	virtual float CalculateValue(const int Level) override;

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
	virtual float SubCrit(const int Level);
	
};
