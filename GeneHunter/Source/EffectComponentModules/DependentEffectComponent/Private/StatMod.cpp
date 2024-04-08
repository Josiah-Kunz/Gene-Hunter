#include "StatMod.h"

#include "MathUtil.h"

void FStatMod::Modify(UCombatStatsComponent* Stats, const bool bIncrease, const bool bPermAndCurrent) const
{

	// Check decrease instead
	float Value = Modification;
	if (!bIncrease)
	{
		// If multiplication, we need to divide instead
		const bool bIsMultipy = Mode == EModificationMode::MultiplyAbsolute || Mode == EModificationMode::MultiplyPercentage;
		if (bIsMultipy)
		{
			// Don't divide by zero
			if (FMathf::Abs(Modification) > FMathf::Epsilon)
			{
				Value = 1/Modification;
			}
		} else	
		{
			Value = -Modification;
		}
	}

	// The one we're responsible for
	UE_LOG(LogTemp, Warning, TEXT("Modifying [%s]"), *UEnum::GetValueAsString(Stat))
	Stats->ModifyStat(Stat, Value, ValueType, Mode);

	// Also the other one?
	if (bPermAndCurrent)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			Stats->ModifyStat(Stat, Value, EStatValueType::Permanent, Mode);
			break;
		case EStatValueType::Permanent:
			Stats->ModifyStat(Stat, Value, EStatValueType::Current, Mode);
			break;
		}
	}
}
