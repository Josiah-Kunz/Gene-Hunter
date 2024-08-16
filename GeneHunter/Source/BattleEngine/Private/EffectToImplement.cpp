#include "EffectToImplement.h"

#include "ComponentUtilities.h"

int32 FEffectToImplement::TryToImplementEffect(AActor* Target)
{

	// Check attachment
	if (FMath::RandRange(0.f, 100.f) > PercentToImplement)
	{
		return 0;
	}

	// Attach!
	UEffectComponent* EffectInstance = NewObject<UEffectComponent>(Target, EffectType->StaticClass());
	if ( EffectInstance )
	{
		Target->AddInstanceComponent(EffectInstance); \
		EffectInstance->RegisterComponent();
	}

	// Normalize stack probabilities
	float Total = 0;
	for(const TPair<uint32, float> Pair : StacksAndPercentages)
	{
		Total += Pair.Value;
	}

	// Check cumulative probability that N stacks will be spawned
	uint32 NumStacks = 1;
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

	// Guard - if there's a typpo, clearly it attached, so there should be at least one stack intended
	if (bStacksSet)
	{
		UE_LOG(LogTemp, Warning,
			TEXT("Number of stacks of [%s] were never set on target [%s]. Surely this is incorrect!"),
			*EffectType->GetFullName(),
			*Target->GetFullName()
			)
	}

	// Set stacks
	EffectInstance->SetStacks(NumStacks);

	// Return that value
	return NumStacks;
	
}
