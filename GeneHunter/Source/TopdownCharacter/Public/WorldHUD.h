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
	 * A running list of which Actors are underneath the mouse (as determined by collider overlap).
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="World Interaction")
	TArray<AActor*> MouseoverActors;

	/**
	 * Tracks Actors and ActorComponents that are currently being overlapped.
	 */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="World Interaction")
	UOverlapTracker* OverlapTracker;

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

	/**
	 * Used to get the currently overlapped UActorComponents (e.g., UCombatStatsComponents). 
	 * @param ComponentType 
	 * @param Components 
	 */
	UFUNCTION(Blueprintable, Category="World Interaction")
	void GetOverlappedComponents(const TSubclassOf<UActorComponent> ComponentType, TArray<UActorComponent*>& Components) const;
	
	virtual void BeginPlay() override;
	
};
