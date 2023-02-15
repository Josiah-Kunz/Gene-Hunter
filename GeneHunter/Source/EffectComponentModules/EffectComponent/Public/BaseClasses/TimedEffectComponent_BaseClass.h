#pragma once

#include "CoreMinimal.h"
#include "EffectComponent.h"
#include "TimedEffectComponent_BaseClass.generated.h"


/**
 * A class for EffectComponents that expire after a certain time. Stackable. This is the base class; you should use 
 *	UBuffComponent_BaseClass or UDebuffComponent_BaseClass.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class EFFECTCOMPONENT_API UTimedEffectComponent_BaseClass : public UEffectComponent
{
	GENERATED_BODY()

public:

	/**
	 * Time until this effect expires.
	 */
	float RemainingTime;

	UTimedEffectComponent_BaseClass();
	
	/**
	 * The duration of this effect when it is first applied.
	 */
	virtual float StartingDuration();

	/**
	 * Sets RemainingTime to StartingDuration.
	 */
	virtual void OnComponentCreated() override;

	/**
	 * Ticks RemainingTime down.
	 */
	virtual void TickComponent(const float DeltaTime, const ELevelTick TickType,
		FActorComponentTickFunction* ThisTickFunction) override;

};
