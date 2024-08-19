#include "ProbabilityContainer.h"

void UProbabilityContainer::AddProbabilityPair(const TSubclassOf<UObject>& InClass, const float InProbability)
{
	ProbabilityPairs.Add(FProbabilityPair(InClass, InProbability));
}

TSubclassOf<UObject> UProbabilityContainer::GetRandomClass() const
{

	// Normalize
	float TotalProbability = 0.0f;
	for (const FProbabilityPair& Pair : ProbabilityPairs)
	{
		TotalProbability += Pair.Probability;
	}

	// See what we pick
	const float Threshold = FMath::RandRange(0.0f, TotalProbability);
	float AccumulatedProbability = 0.0f;
	for (const FProbabilityPair& Pair : ProbabilityPairs)
	{
		AccumulatedProbability += Pair.Probability;
		if (Threshold <= AccumulatedProbability)
		{
			return Pair.Class;
		}
	}

	return nullptr;
}
