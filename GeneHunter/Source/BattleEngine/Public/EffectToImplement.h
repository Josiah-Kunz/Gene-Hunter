#pragma once

#include "EffectComponent.h"

#include "EffectToImplement.generated.h"

USTRUCT(Blueprintable)
struct BATTLEENGINE_API FEffectToImplement
{

	GENERATED_BODY()

public:
	/**
	 * The EffectComponent to attach to the target.
	 */
	UPROPERTY(EditAnywhere, Category="Effect to Implement")
	TSubclassOf<UEffectComponent> EffectType;

	/**
	 * Percent (not fraction) that the Effect will attach to the target. Note that this is *not* normalized and is
	 * actually out of 100%. This is because we could have multiple Effects hit or not.
	 */
	UPROPERTY(EditAnywhere, Category="Effect to Implement")
	float PercentToImplement = 100;

	/**
	 * Number of stacks on the Effect at attachment (provided the Effect actually attaches) and the relative probability
	 * of attaching. Note that the probabilities don't have to add to 100 (they are normalized before calculation), but
	 * it's probably clearer if they do.
	 */
	UPROPERTY(EditAnywhere, Category="Effect to Implement")
	TMap<uint32, float> StacksAndPercentages = {
		{1, 100}
	};

	/**
	 * Calculates the number of stack to inflict upon a target. 0 = fail.
	 */
	uint16 CalculateNumStacks();

	/**
	 * Attaches the Effect of EffectType to the Target.
	 */
	void ImplementEffect(const uint16 NumStacks, AActor* Target);
	
};
