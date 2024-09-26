// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTargetingComponent.h"
#include "Components/SceneComponent.h"
#include "MouseoverTrigger.generated.h"

/**
 * When the collider detects a mouseover event, it sends the information to the current player's targeting component.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TOPDOWNCHARACTER_API UMouseoverTrigger : public USceneComponent
{
	GENERATED_BODY()

public:

	/**
	 * This can be assigned in the Blueprint. If it's not part of the RootComponent, it won't follow the Actor around.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	UShapeComponent* CollisionComponent;
	
	UMouseoverTrigger();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UPlayerTargetingComponent* PlayerTargetingComponent;

	UPROPERTY()
	FScriptDelegate BeginDelegate, EndDelegate;

	UFUNCTION()
	void SendMouseoverInfo(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void RetractMouseoverInfo(UPrimitiveComponent* TouchedComponent);
	
};
