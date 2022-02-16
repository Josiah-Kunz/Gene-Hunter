


#include "Type.h"

TArray<UType*> UType::GetDamageTypesBetween(const float Min, const float Max, const bool Inclusive)
{
	TArray<UType*> Ret;
	for(const auto& Pair : AttackModifiers)
	{
		if (Inclusive)
		{
			if (Min <= Pair.Value.Modifier && Pair.Value.Modifier <= Max)
				Ret.Add(Pair.Key);
		} else
		{
			if (Min < Pair.Value.Modifier && Pair.Value.Modifier < Max)
				Ret.Add(Pair.Key);
		}
	}
	return Ret;
}

TArray<UType*> UType::GetIncreasedDamageTypes()
{
	return GetDamageTypesBetween(1, INFINITY, false);
}

TArray<UType*> UType::GetDecreasedDamageTypes()
{
	return GetDamageTypesBetween(0, 1, false);
}

TArray<UType*> UType::GetHealedDamageTypes()
{
	return GetDamageTypesBetween(-INFINITY, 0, false);
}

TArray<UType*> UType::GetNeutralDamageTypes()
{
	return GetDamageTypesBetween(1, 1);
}

TArray<UType*> UType::GetImmuneTypes()
{
	return GetDamageTypesBetween(0, 0);
}

