#include "Affinity.h"

bool FAffinity::IsLocked() const
{
	return bLocked;
}

void FAffinity::SetLockedState(const bool bLockedState)
{
	bLocked = bLockedState;
	CurrentPoints = FMath::Max(CurrentPoints, 1);
}
