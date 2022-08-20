// 

#pragma once

#include "Stat.h"
#include "StandardStat.generated.h"

USTRUCT(Blueprintable)
struct STATSCOMPONENT_API FStandardStat : public FStat
{
	GENERATED_BODY()
	
public:
	virtual float CalculateValue(const int Level) override;
};
