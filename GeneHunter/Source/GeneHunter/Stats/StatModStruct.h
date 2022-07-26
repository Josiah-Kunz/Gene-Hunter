#pragma once

#include "Stat.h"
#include "StatModStruct.generated.h"

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
