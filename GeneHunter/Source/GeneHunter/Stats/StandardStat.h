// 

#pragma once

#include "GeneHunter/Stats/Stat.h"
#include "StandardStat.generated.h"

USTRUCT(Blueprintable)
struct GENEHUNTER_API FStandardStat : public FStat
{
	GENERATED_BODY()
	
public:
	virtual float CalculateValue(const int Level) override;
};
