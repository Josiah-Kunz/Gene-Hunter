// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatStatsComponent.h"
#include "CoreMinimal.h"
#include "HealthBarWidget.h"
#include "LevelComponent.h"
#include "PaperZDCharacter.h"
#include "Components/WidgetComponent.h"


#include "TopdownCharacter.generated.h"

/**
 * Base C++ class that sets up the LevelComponent and CombatStatsComponent. Does not set up the HealthBarWidget since
 * its transform needs to be set on a per-character basis.
 */
UCLASS()
class TOPDOWNCHARACTER_API ATopdownCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	ATopdownCharacter();

	virtual void PostInitializeComponents() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Required Components")
	ULevelComponent* Level;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category="Required Components")
	UCombatStatsComponent* CombatStats;
	
	
};
