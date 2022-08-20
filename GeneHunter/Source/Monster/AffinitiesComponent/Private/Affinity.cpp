#include "Affinity.h"

#include "../../../../Plugins/Developer/RiderLink/Source/RD/thirdparty/spdlog/include/spdlog/async_logger.h"

bool FAffinity::IsLocked() const
{
	return bLocked;
}

void FAffinity::SetLockedState(const bool bLockedState)
{
	bLocked = bLockedState;
	CurrentPoints = FMath::Max(CurrentPoints, 1);
}
