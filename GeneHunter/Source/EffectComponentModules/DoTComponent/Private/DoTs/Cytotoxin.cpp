#include "Cytotoxin.h"

float UCytotoxin::StartingDuration()
{
	return 3;
}

int32 UCytotoxin::MaxStacks()
{
	return 3;
}

EModificationMode UCytotoxin::Mode()
{
	return EModificationMode::AddPercentage;
}

float UCytotoxin::DPS()
{
	return 1;
}
