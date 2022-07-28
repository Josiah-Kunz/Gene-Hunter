﻿#pragma once

#include "Stat.h"
#include "StatModStruct.generated.h"

/**
 * Mostly used for StatsBlock::ModifyStats.
 */
USTRUCT(Blueprintable)
struct FStatModStruct
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FStat Stat;

	UPROPERTY()
	int Mod;
};
