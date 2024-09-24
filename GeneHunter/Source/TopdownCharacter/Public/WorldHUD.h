// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatStatsComponent.h"
#include "OverlapTracker.h"
#include "GameFramework/HUD.h"
#include "WorldHUD.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class TOPDOWNCHARACTER_API AWorldHUD : public AHUD
{
	GENERATED_BODY()

public:
	
	/**
	 * The world location of the mouse (discounting the z).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="World Interaction")
	FVector MouseWorldLocation;

	/**
	 * A normalized unit vector from the player to the mouse's world position.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="World Interaction")
	FVector MouseWorldDirection;
	
};
