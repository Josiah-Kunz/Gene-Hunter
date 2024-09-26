// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerTargetingComponent.h"
#include "Components/SceneComponent.h"
#include "UObject/ScriptDelegates.h"

#include "MouseoverTrigger.generated.h"

/**
 * When the collider detects a mouseover event, it sends the information to the current player's targeting component.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UMouseoverTrigger : public USceneComponent
{
	GENERATED_BODY()

public:

	/**
	 * This can be assigned in the Blueprint and bound to delegates via SetCollisionComponent.
	 *
	 * If it is assigned, make sure it's part of the RootComponent or it won't follow the Actor around.
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Overlap")
	UShapeComponent* CollisionComponent;

	UFUNCTION(BlueprintCallable, Category = "Overlap")
	void SetCollisionComponent(UShapeComponent* NewCollisionComponent);
	
	UMouseoverTrigger();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	UPlayerTargetingComponent* PlayerTargetingComponent;

	UFUNCTION()
	void SendMouseoverInfo(UPrimitiveComponent* TouchedComponent);

	UFUNCTION()
	void RetractMouseoverInfo(UPrimitiveComponent* TouchedComponent);

	bool bEventsAreBound;
	
};
