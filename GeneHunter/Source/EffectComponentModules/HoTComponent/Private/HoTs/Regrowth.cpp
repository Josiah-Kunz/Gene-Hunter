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

EStatReferenceType URegrowth::StatReferenceType()
{
	return EStatReferenceType::Permanent;
}

float URegrowth::HPS()
{
	return 1;
}

float URegrowth::TickDuration()
{
	return 1;
}
