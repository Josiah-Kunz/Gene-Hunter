// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CombatStatsComponent.h"
#include "CoreMinimal.h"
#include "LevelComponent.h"
#include "PaperZDCharacter.h"


#include "TopdownCharacter.generated.h"

UCLASS()
class TOPDOWNCHARACTER_API ATopdownCharacter : public APaperZDCharacter
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, Category="Required Components")
	UCombatStatsComponent* CombatStats;

	UPROPERTY(EditAnywhere, Category="Required Components")
	ULevelComponent* Level;
	
	
};
