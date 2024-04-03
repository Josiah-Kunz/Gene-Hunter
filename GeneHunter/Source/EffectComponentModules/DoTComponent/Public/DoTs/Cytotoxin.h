#pragma once

#include "CoreMinimal.h"
#include "DoTComponent.h"
#include "Cytotoxin.generated.h"

/**
 * Deals 1% Health per second for 5 seconds. Max 3 stacks.
 */
UCLASS(ClassGroup=(Monster), meta=(BlueprintSpawnableComponent))
class DOTCOMPONENT_API UCytotoxin : public UDoTComponent
{
	GENERATED_BODY()

public:

	virtual float StartingDuration() override;

	virtual int32 MaxStacks() override;

	virtual float DPS() override;

	virtual EModificationMode Mode() override;
	
};