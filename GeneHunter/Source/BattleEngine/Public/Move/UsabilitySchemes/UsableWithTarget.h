// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTargetingComponent.h"
#include "MoveUsabilityScheme.h"
#include "UsableWithTarget.generated.h"

/**
 * Returns true when the nearby CombatTargetingComponent returns GetTarget that is non-null.
 */
UCLASS()
class BATTLEENGINE_API AUsableWithTarget : public AMoveUsabilityScheme
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UCombatTargetingComponent* TargetingComponent;

	void Initialize_Implementation(AActor* NewOwner) override;

	bool IsUsable_Implementation() override;
	
};
