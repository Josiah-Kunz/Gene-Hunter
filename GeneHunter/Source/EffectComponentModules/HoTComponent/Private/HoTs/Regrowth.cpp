#include "Regrowth.h"

float URegrowth::GetAmount()
{
	return StatsComponent->GetStat(EStatEnum::Health).GetPermanentValue() * 0.01f * GetStacks();
}

float URegrowth::GetTickRate()
{
	return 1;
}

float URegrowth::StartingDuration()
{
	return 5;
}
