


#include "Type.h"

#pragma region Getting modifiers when attacking

TArray<UType*> UType::GetAttackingTypesBetween(const float Min, const float Max, const bool Inclusive)
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

TArray<UType*> UType::GetEffectiveAgainstTypes()
{
	return GetAttackingTypesBetween(1, INFINITY, false);
}

TArray<UType*> UType::GetIneffectiveAgainstTypes()
{
	return GetAttackingTypesBetween(0, 1, false);
}

TArray<UType*> UType::GetHealsTypes()
{
	return GetAttackingTypesBetween(-INFINITY, 0, false);
}

TArray<UType*> UType::GetNeutralAttackTypes()
{
	return GetAttackingTypesBetween(1, 1);
}

TArray<UType*> UType::GetZeroDamageToTypes()
{
	return GetAttackingTypesBetween(0, 0);
}

void UType::SortTypesAttacking(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	Sorted.Sort([Min, Max, Inclusive](const UType& A, const UType& B)
	{
		int CountA = 0;
		for(const auto& Pair : A.AttackModifiers)
		{
			if (Inclusive)
			{
				if (Min <= Pair.Value.Modifier && Pair.Value.Modifier <= Max)
					CountA++;
			} else
			{
				if (Min < Pair.Value.Modifier && Pair.Value.Modifier < Max)
					CountA++;
			}
		}
		int CountB = 0;
		for(const auto& Pair : B.AttackModifiers)
		{
			if (Inclusive)
			{
				if (Min <= Pair.Value.Modifier && Pair.Value.Modifier <= Max)
					CountB++;
			} else
			{
				if (Min < Pair.Value.Modifier && Pair.Value.Modifier < Max)
					CountB++;
			}
		}
		return CountA > CountB;
	});
}


#pragma endregion

#pragma region Getting modifiers when defending

TArray<UType*> UType::GetDefendingTypesBetween(const float Min, const float Max, const bool Inclusive)
{
	TArray<UType*> Ret;
	for(const auto& Pair : AttackModifiers)	// If the attacking matchup doesn't exist, we can't do the defending matchup either
	{
		if (Inclusive)
		{
			if (Min <= Pair.Key->AttackModifiers[this].Modifier && Pair.Key->AttackModifiers[this].Modifier <= Max)
				Ret.Add(Pair.Key);
		} else
		{
			if (Min < Pair.Key->AttackModifiers[this].Modifier && Pair.Key->AttackModifiers[this].Modifier < Max)
				Ret.Add(Pair.Key);
		}
	}
	return Ret;
}

TArray<UType*> UType::GetWeakToTypes()
{
	return GetDefendingTypesBetween(1, INFINITY, false);
}

TArray<UType*> UType::GetResistsTypes()
{
	return GetDefendingTypesBetween(0, 1, false);
}

TArray<UType*> UType::GetHealedByTypes()
{
	return GetDefendingTypesBetween(-INFINITY, 0, false);
}

TArray<UType*> UType::GetNeutralDefendTypes()
{
	return GetDefendingTypesBetween(1, 1);
}

TArray<UType*> UType::GetImmuneToTypes()
{
	return GetDefendingTypesBetween(0, 0);
}

void UType::SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	Sorted.Sort([Types, Min, Max, Inclusive](const UType& A, const UType& B)
	{
		float Modifier;
		int CountA = 0;
		for(const UType* Attacker : Types)
		{
			Modifier = Attacker->AttackModifiers.Find(std::addressof(A))->Modifier;
			if (Inclusive)
			{
				if (Min <= Modifier && Modifier <= Max)
					CountA++;
			} else
			{
				if (Min < Modifier && Modifier < Max)
					CountA++;
			}
		}

		int CountB = 0;
		for(const UType* Attacker : Types)
		{
			Modifier = Attacker->AttackModifiers.Find(std::addressof(A))->Modifier;
			if (Inclusive)
			{
				if (Min <= Modifier && Modifier <= Max)
					CountB++;
			} else
			{
				if (Min < Modifier && Modifier < Max)
					CountB++;
			}
		}
		
		return CountA > CountB;
	});
}

#pragma endregion