// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTargetingComponent.h"
#include "PlayerTargetingComponent.generated.h"


UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UPlayerTargetingComponent : public UCombatTargetingComponent
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;
	
	virtual FVector GetAttackVector() override;

private:

	UPROPERTY()
	APlayerController* PlayerController;

	FVector2D GetPlayerToMouseVector() const;
	
};
