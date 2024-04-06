#include "StatMod.h"

void FStatMod::Modify(UCombatStatsComponent* Stats, const int8 Scale, const bool bPermAndCurrent) const
{

	// The one we're responsible for
	Stats->ModifyStat(Stat, Modification * Scale, ValueType, Mode);

	// Also the other one?
	if (bPermAndCurrent)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			Stats->ModifyStat(Stat, Modification * Scale, EStatValueType::Permanent, Mode);
			break;
		case EStatValueType::Permanent:
			Stats->ModifyStat(Stat, Modification * Scale, EStatValueType::Current, Mode);
			break;
		}
	}
}
