#include "EffectToImplement.h"

uint16 FEffectToImplement::CalculateNumStacks()
{

	// Check attachment
	if (FMath::RandRange(0.f, 100.f) > PercentToImplement)
	{
		return 0;
	}

	// Normalize stack probabilities
	float Total = 0;
	for(const TPair<uint32, float> Pair : StacksAndPercentages)
	{
		Total += Pair.Value;
	}

	// Check cumulative probability that N stacks will be spawned
	uint16 NumStacks = 1;
	bool bStacksSet = false;
	const float Threshold = FMath::RandRange(0.f, Total);
	float Cumulative = 0;
	for(const TPair<uint32, float> Pair : StacksAndPercentages)
	{
		// This iteration
		Cumulative += Pair.Value;

		// Check if this triggers success
		if (Cumulative > Threshold)
		{
			NumStacks = Pair.Key;
			bStacksSet = true;
			break;
		}
	}

	// Guard - if there's a typpo, clearly it should be attached, so there should be at least one stack intended
	if (bStacksSet)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Number of stacks of [%s] were never set on target. Surely this is incorrect!"),
			*EffectType->GetFullName()
			)
	}

	// Return that value
	return NumStacks;
	
}

void FEffectToImplement::ImplementEffect(const uint16 NumStacks, AActor* Target)
{

	// Attach
	UEffectComponent* EffectInstance = NewObject<UEffectComponent>(Target, EffectType->StaticClass());
	if (EffectInstance)
	{
		Target->AddInstanceComponent(EffectInstance); 
		EffectInstance->RegisterComponent();
	}

	// Set stacks
	EffectInstance->SetStacks(NumStacks);
}
