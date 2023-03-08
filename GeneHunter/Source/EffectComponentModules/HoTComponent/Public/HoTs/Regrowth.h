#pragma once

#include "CoreMinimal.h"
#include "HoTComponent.h"
#include "Regrowth.generated.h"

/**
 * Heals 1% Health per second for 5 seconds. Max 3 stacks.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class HOTCOMPONENT_API URegrowth : public UHoTComponent
{
	GENERATED_BODY()

public:

	virtual float GetAmount() override;

	virtual float GetTickRate() override;

	virtual float StartingDuration() override;
	
};

