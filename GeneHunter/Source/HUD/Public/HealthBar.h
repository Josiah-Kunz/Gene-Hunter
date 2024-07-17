// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CombatStatsComponent.h"
#include "Components/ProgressBar.h"

#include "HealthBar.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class HUD_API UHealthBar : public UActorComponent
{
	GENERATED_BODY()

#pragma region Variables
	
public:

	UPROPERTY()
	TSubclassOf<UUserWidget> ProgressBarClass = UProgressBar::StaticClass();

private:
	
	FCombatStat HealthStat;

	TObjectPtr<UUserWidget> MainBar;

#pragma endregion

#pragma region Functions
	
public:
	
	UHealthBar();

protected:

	virtual void OnComponentCreated() override;
	
	virtual void BeginPlay() override;

private:

	void SetMainBar();

#pragma endregion

};
