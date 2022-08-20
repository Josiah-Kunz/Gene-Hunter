#pragma once

#include "Stat.h"
#include "StatModStruct.generated.h"

/**
 * Mostly used for StatsComponent::ModifyStats.
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
