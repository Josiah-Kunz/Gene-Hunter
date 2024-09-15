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

	virtual UCombatStatsComponent* GetTarget() override;

private:

	UPROPERTY()
	APlayerController* PlayerController;

	/**
	 * 
	 * @param WorldLocation The position of the mouse in world space.
	 * @param WorldDirection The (unnormalized) vector from the player to the mouse.
	 */
	void GetPlayerToMouseVector(FVector& WorldLocation, FVector& WorldDirection) const;

	/**
	 * Determines whether or not the PlayerController exists. If not, it gives a warning message.
	 * @return 
	 */
	bool DoesPCExist() const;

	const FVector2D DefaultVector = FVector2D::ZeroVector;
	
};
