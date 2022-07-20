// 

#pragma once

#include "GeneHunter/Stats/Stat.h"
#include "StandardStat.generated.h"

/**
 * 
 */
UCLASS()
class GENEHUNTER_API UStandardStat : public UStat
{
	GENERATED_BODY()
	
public:
	virtual float CalculateValue(const int Level) override;
};
