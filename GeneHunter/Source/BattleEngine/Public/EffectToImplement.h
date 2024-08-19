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
	 * Attempts to inflict the Effect onto the Target.
	 * @param Target 
	 * @return The number of stacks inflicted upon the Target. 0 = fail.
	 */
	int32 TryToImplementEffect(AActor* Target);
	
};
