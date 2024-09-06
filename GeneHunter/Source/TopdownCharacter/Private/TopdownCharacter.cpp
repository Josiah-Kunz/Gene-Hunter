// Fill out your copyright notice in the Description page of Project Settings.


#include "TopdownCharacter.h"

#include "ComponentUtilities.h"

ATopdownCharacter::ATopdownCharacter()
{
	Level = CreateDefaultSubobject<ULevelComponent>(TEXT("Level"));
	CombatStats = CreateDefaultSubobject<UCombatStatsComponent>(TEXT("Combat Stats"));
	CombatStats->LevelComponent = Level;
	CombatStats->RandomizeStats();
}

void ATopdownCharacter::PostInitializeComponents()
{

	// Supah!
	Super::PostInitializeComponents();

	// Stats
	if (CombatStats->LevelComponent == nullptr)
	{
		CombatStats->DestroyComponent();
		Level->DestroyComponent();
		Level = CreateDefaultSubobject<ULevelComponent>(TEXT("Level"));
		CombatStats = CreateDefaultSubobject<UCombatStatsComponent>(TEXT("Combat Stats"));
		CombatStats->LevelComponent = Level;
		CombatStats->RandomizeStats();
	}
}

