#pragma once

#include "CoreMinimal.h"
#include "OverlapTracker.h"
#include "UsableWithTarget.h"
#include "UsableTargetInRange.generated.h"

UCLASS()
class BATTLEENGINE_API AUsableTargetInRange : public AUsableWithTarget
{
	GENERATED_BODY()

public:


	virtual void Initialize_Implementation(AActor* NewOwner) override;

	virtual bool IsUsable_Implementation() override;

private:

	/**
	 * Usability then depends on if the Target is within the Trackers' ranges.
	 */
	UPROPERTY()
	TArray<UOverlapTracker*> Trackers;
	
};
