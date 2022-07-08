// 

#pragma once

#include "GeneHunter/Stats/Stat.h"
#include "Haste.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UHaste : public UStat
{
	GENERATED_BODY()

	

public:
	/**
	 * Calculates the value of this Stat based on a unique formula. See the Stats document for relevant equations.
	 * @param Level The level (always positive).
	 */
	UFUNCTION(BlueprintCallable)
	virtual float CalculateValue(const int Level) override;

	/**
	 * This Stat's description and such.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FSupportingText const* SupportingText() const override;
	
	/**
	 * The name of this Stat to be displayed (such as "Physical Attack").
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FString const* Name() const override;

	/**
	 * A shorter version of Name (such as "PhA" for "Physical Attack").
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FString const* Abbreviation() const override;

	/**
	 * The color associated with this Stat.
	 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	virtual FLinearColor const* Color() const override;
	
};
