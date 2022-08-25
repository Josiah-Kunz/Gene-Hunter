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

int FAffinity::GetCurrentPoints() const
{
	return CurrentPoints;
}

void FAffinity::SetCurrentPoints(const int NewPoints)
{

	// Nonnegative only
	CurrentPoints = FMath::Max(NewPoints,  IsLocked() ? 1 : 0);

	// Not greater than max
	CurrentPoints = FMath::Min(CurrentPoints, MaxPoints);
}

int FAffinity::GetMaxPoints() const
{
	return MaxPoints;
}

void FAffinity::SetMaxPoints(const int NewMax)
{

	// Positive only
	MaxPoints = FMath::Max(NewMax, 1);

	// Set current accordingly
	SetCurrentPoints(GetCurrentPoints());}
