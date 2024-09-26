// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CombatTargetingComponent.h"
#include "WorldHUD.h"
#include "PlayerTargetingComponent.generated.h"


UCLASS(Blueprintable, meta=(BlueprintSpawnableComponent))
class BATTLEENGINE_API UPlayerTargetingComponent : public UCombatTargetingComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	TArray<AActor*> MouseoverActors;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Targeting")
	TArray<UCombatStatsComponent*> MouseoverStats;
	
	UPlayerTargetingComponent();
	
	virtual void BeginPlay() override;
	
	virtual FVector GetAttackVector() override;

	virtual UCombatStatsComponent* GetTarget() override;

private:
	
	/**
	 * The WorldHUD tracks the mouse position.
	 */
	UPROPERTY()
	AWorldHUD* HUD;

	/**
	 * Determines whether or not the HUD exists. If not, it gives a warning message.
	 * @return 
	 */
	bool DoesHUDExist() const;

	const FVector2D DefaultVector = FVector2D::ZeroVector;
	
};
