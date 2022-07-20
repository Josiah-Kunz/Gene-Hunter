// 

#pragma once

#include "GeneHunter/Stats/StandardStat.h"
#include "SpecialDefense.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API USpecialDefense : public UStandardStat
{
	GENERATED_BODY()

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
