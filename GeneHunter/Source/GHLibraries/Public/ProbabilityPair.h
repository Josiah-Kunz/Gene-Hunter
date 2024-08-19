#pragma once

#include "CoreMinimal.h"

#include "ProbabilityPair.generated.h"

/**
 * A structure to store classes of UObjects and their relative probabilities. Example:
 * 
 *	1) Suppose you want a Pokemon-style Move that has a 30% chance to Sleep, 30% chance to Burn, and 30% chance to
 *		Paralyze. You would use this (in conjunction with ProbabilityContainer) to execute this. Here, the Class
 *		is UEffectComponent (a UActorComponent).
 *
 *	2) Suppose you want a Pokemon-style random encounter: 1% to fight a Clefairy, 10% to fight a Geodude, and 70%
 *		chance to fight a Zubat. You would again use this in conjunction with ProbabilityContainer. Here the Class is
 *		Species (a UPrimaryDataAsset).
 */
USTRUCT(BlueprintType)
struct GHLIBRARIES_API FProbabilityPair
{
	GENERATED_BODY()

	/**
	 * The type of UObject you want in the pool.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Probability")
	TSubclassOf<UObject> Class;

	/**
	 * The relative probability. This can be out of 1, 100, or whatever number you want since all entries in the
	 *	ProbabilityContainer are normalized.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random Probability")
	float Probability;

	FProbabilityPair() : Class(nullptr), Probability(100.f) {}
	FProbabilityPair(const TSubclassOf<UObject> InClass, const float InProbability) :
		Class(InClass), Probability(InProbability) {}
};