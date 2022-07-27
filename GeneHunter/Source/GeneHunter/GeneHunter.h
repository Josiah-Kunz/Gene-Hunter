// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "GeneHunter/StatsBlock/StatsBlock.h"
#include "GeneHunter/StatsBlock/StatsBlockDetailsPanel.h"

class FGeneHunterModule : public IModuleInterface{

public:
	virtual void StartupModule() override;

	virtual void ShutdownModule() override;
	
};