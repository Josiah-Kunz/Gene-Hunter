#include "Regrowth.h"

float URegrowth::StartingDuration()
{
	return 5;
}

int32 URegrowth::MaxStacks()
{
	return 3;
}

EModificationMode URegrowth::Mode()
{
	return EModificationMode::AddPercentage;
}

float URegrowth::HPS()
{
	return 1;
}

float URegrowth::TickDuration()
{
	return 1;
}
