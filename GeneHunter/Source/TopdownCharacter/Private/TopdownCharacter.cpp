// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownCharacter.h"

#include "ComponentUtilities.h"

ATopdownCharacter::ATopdownCharacter()
{
	Level = CreateDefaultSubobject<ULevelComponent>(TEXT("Level"));
	CombatStats = CreateDefaultSubobject<UCombatStatsComponent>(TEXT("Combat Stats"));
}

void ATopdownCharacter::PostInitializeComponents()
{

	// Supah!
	Super::PostInitializeComponents();

	// Stats
	CombatStats->LevelComponent = Level;
	CombatStats->RandomizeStats();
}

