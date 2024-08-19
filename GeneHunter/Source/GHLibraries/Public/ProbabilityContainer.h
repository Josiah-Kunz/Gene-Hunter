#pragma once

#include "CoreMinimal.h"
#include "ProbabilityPair.h"

#include "ProbabilityContainer.generated.h"

/**
 * A way to store classes of UObjects and their relative probabilities. Example:
 * 
 *	1) Suppose you want a Pokemon-style Move that has a 30% chance to Sleep, 30% chance to Burn, and 30% chance to
 *		Paralyze. You would use this as:
 *
 *		i) The ProbabilityPairs would be:
 *			{Sleep, 30},
 *			{Burn, 30},
 *			{Paralyze, 30}
 *			{nullptr, 10}	// Otherwise, each effect has 33.3% chance to work
 *		Note that this could also be {Sleep, 0.3}, {Burn, 0.3}, etc.
 *
 *		ii) When the Move hits and we're ready to roll the dice, we'd use GetRandomClass() and implement the effect
 *		accordingly.
 *
 *	2) Suppose you want a Pokemon-style random encounter: 1% to fight a Clefairy, 10% to fight a Geodude, and 70%
 *		chance to fight a Zubat. You would again use this as:
 *
 *		i) The ProbabilityPairs are:
 *			{Clefairy (a UPrimaryDataAsset), 1},
 *			{Geodude, 10},
 *			{Zubat, 70},
 *			{nullptr, 19}
 */
UCLASS(Blueprintable)
class GHLIBRARIES_API UProbabilityContainer : public UObject
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Probability")
	TArray<FProbabilityPair> ProbabilityPairs;

	UFUNCTION(BlueprintCallable, Category = "Random Probability")
	void AddProbabilityPair(const TSubclassOf<UObject>& InClass, const float InProbability);

	UFUNCTION(BlueprintCallable, Category = "Random Probability")
	TSubclassOf<UObject> GetRandomClass() const;
};