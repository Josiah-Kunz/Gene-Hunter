// 

#pragma once

#include"CombatStat.h"
#include "StandardStat.generated.h"

USTRUCT(Blueprintable)
struct COMBATSTATSCOMPONENT_API FStandardStat : public FCombatStat
{
	GENERATED_BODY()
	
public:
	virtual float CalculateValue(const uint16 Level) override;
};
