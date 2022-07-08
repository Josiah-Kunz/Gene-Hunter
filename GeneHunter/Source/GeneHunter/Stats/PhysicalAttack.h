// 

#pragma once

#include "GeneHunter/Stats/StandardStat.h"
#include "PhysicalAttack.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UPhysicalAttack : public UStandardStat
{
	GENERATED_BODY()

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
