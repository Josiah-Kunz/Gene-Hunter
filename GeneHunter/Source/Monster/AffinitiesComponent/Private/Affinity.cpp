#include "Affinity.h"

bool FAffinity::IsLocked() const
{
	return bLocked;
}

void FAffinity::SetLockedState(const bool bLockedState)
{
	bLocked = bLockedState;
	CurrentPoints = FMath::Max(CurrentPoints, static_cast<uint8>(1));
}

uint8 FAffinity::GetCurrentPoints() const
{
	return CurrentPoints;
}

void FAffinity::SetCurrentPoints(const uint8 NewPoints)
{

	// Nonnegative only
	CurrentPoints = FMath::Max(NewPoints, static_cast<uint8>(IsLocked() ? 1 : 0));

	// Not greater than max
	CurrentPoints = FMath::Min(CurrentPoints, MaxPoints);
}

uint8 FAffinity::GetMaxPoints() const
{
	return MaxPoints;
}

void FAffinity::SetMaxPoints(const uint8 NewMax)
{

	// Positive only
	MaxPoints = FMath::Max(NewMax, static_cast<uint8>(1));

	// Set current accordingly
	SetCurrentPoints(GetCurrentPoints());}
