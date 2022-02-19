


#include "Type.h"

#pragma region Getting modifiers when attacking

float UType::GetModifierWhenAttacked(const TArray<UType*> AttackingTypes) const
{
	float Ret = 1;
	for(const UType* Attacker : AttackingTypes)
		Ret *= Attacker->AttackModifiers[this].Modifier;
	return Ret;
}


TArray<UType*> UType::GetAttackingTypesBetween(const float Min, const float Max, const bool Inclusive) const
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

TArray<UType*> UType::GetEffectiveAgainstTypes() const
{
	return GetAttackingTypesBetween(1, INFINITY, false);
}

TArray<UType*> UType::GetIneffectiveAgainstTypes() const
{
	return GetAttackingTypesBetween(0, 1, false);
}

TArray<UType*> UType::GetHealsTypes() const
{
	return GetAttackingTypesBetween(-INFINITY, 0, false);
}

TArray<UType*> UType::GetNeutralAttackTypes() const
{
	return GetAttackingTypesBetween(1, 1);
}

TArray<UType*> UType::GetZeroDamageToTypes() const
{
	return GetAttackingTypesBetween(0, 0);
}




#pragma endregion

#pragma region Getting modifiers when defending

TArray<UType*> UType::GetDefendingTypesBetween(const float Min, const float Max, const bool Inclusive) const
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

TArray<UType*> UType::GetWeakToTypes() const
{
	return GetDefendingTypesBetween(1, INFINITY, false);
}

TArray<UType*> UType::GetResistsTypes() const
{
	return GetDefendingTypesBetween(0, 1, false);
}

TArray<UType*> UType::GetHealedByTypes() const
{
	return GetDefendingTypesBetween(-INFINITY, 0, false);
}

TArray<UType*> UType::GetNeutralDefendTypes() const
{
	return GetDefendingTypesBetween(1, 1);
}

TArray<UType*> UType::GetImmuneToTypes() const
{
	return GetDefendingTypesBetween(0, 0);
}

#pragma endregion

#pragma region Sorting for debug purposes

void UType::SortTypesAttacking(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	Sorted.Sort([Min, Max, Inclusive](const UType& A, const UType& B)
	{
		const int NumA = A.GetAttackingTypesBetween(Min, Max, Inclusive).Num();
		const int NumB = B.GetAttackingTypesBetween(Min, Max, Inclusive).Num();
		if (NumA == NumB)
		{
			// Getting "resisted" Types; tiebreaker is "badness" (least number of advantages)
			if (Min < 1)
				return A.GetAttackingTypesBetween(Max, INFINITY, false).Num() < B.GetAttackingTypesBetween(Max, INFINITY, false).Num();
			
			// Getting "effective" Types; tiebreaker is "goodness" (least number of resisted Types)
			return A.GetAttackingTypesBetween(-INFINITY, Min, false).Num() < B.GetAttackingTypesBetween(-INFINITY, Min, false).Num();
		}
		return NumA > NumB;
	});
}

void UType::SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	Sorted.Sort([Min, Max, Inclusive](const UType& A, const UType& B)
	{
		const int NumA = A.GetDefendingTypesBetween(Min, Max, Inclusive).Num();
		const int NumB = B.GetDefendingTypesBetween(Min, Max, Inclusive).Num();
		if (NumA == NumB)
		{
			// Getting "resisted" Types; tiebreaker is "goodness" (least number of weaknesses)
			if (Min < 1)
				return A.GetDefendingTypesBetween(Max, INFINITY, false).Num() < B.GetDefendingTypesBetween(Max, INFINITY, false).Num();
			
			// Getting "weak to" Types; tiebreaker is "badness" (least number of resisted Types)
			return A.GetDefendingTypesBetween(-INFINITY, Min, false).Num() < B.GetDefendingTypesBetween(-INFINITY, Min, false).Num();
		}
		return NumA > NumB;
	});
}

void UType::SortTypesAttackingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted)
{
	Sorted = Types;
	Sorted.Sort([](const UType&A, const UType& B)
	{
		// Get ratios for A and B
		const int EffectiveA = A.GetAttackingTypesBetween(1, INFINITY, false).Num();
		const int IneffectiveA = A.GetAttackingTypesBetween(-INFINITY, 1, false).Num();
		if (IneffectiveA == 0)
			return true;
		const int EffectiveB = B.GetAttackingTypesBetween(1, INFINITY, false).Num();
		const int IneffectiveB = B.GetAttackingTypesBetween(-INFINITY, 1, false).Num();
		if (IneffectiveB == 0)
			return false;
		float RatioA = EffectiveA/static_cast<float>(IneffectiveA);
		float RatioB = EffectiveB/static_cast<float>(IneffectiveB);
		
		// If equal, defer to the one whose numerator is bigger
		if (FMath::IsNearlyEqual(RatioA, RatioB))
			return EffectiveA > EffectiveB;

		// Judge accordingly
		return  RatioA > RatioB ;
	});
}

void UType::SortTypesDefendingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted)
{
	Sorted = Types;
	Sorted.Sort([](const UType&A, const UType& B)
	{
		// Get ratios for A and B
		const int ResistedA = A.GetDefendingTypesBetween(-INFINITY, 1, false).Num();
		const int WeakToA = A.GetDefendingTypesBetween(1, INFINITY, false).Num();
		if (WeakToA == 0)
			return true;
		const int ResistedB = B.GetDefendingTypesBetween(-INFINITY, 1, false).Num();
		const int WeakToB = B.GetDefendingTypesBetween(1, INFINITY, false).Num();
		if (WeakToB == 0)
			return false;
		float RatioA = ResistedA/static_cast<float>(WeakToA);
		float RatioB = ResistedB/static_cast<float>(WeakToB);
		
		// If equal, defer to the one whose numerator is bigger
		if (FMath::IsNearlyEqual(RatioA, RatioB))
			return ResistedA > ResistedB;

		// Judge accordingly
		return  RatioA > RatioB ;
	});
}

void UType::GetNeutralCoverage(const TArray<UType*> Types, TArray<UType*>& NeutralCoverage, const int NumTypes)
{
	TArray<TArray<UType*>> TestedCombos;	// Reduces double-dipping (e.g., Fire/Water is the same as Water/Fire)
	TArray<UType*> TypeCombos;				// Current combination to test
	bool bSuccess;							// Determines if all Types were hit at least neutrally
	for(UType* Type : Types)
	{

		// Build this iteration of the Type combination
		TypeCombos.Empty();
		TypeCombos.Add(Type);
		for(int i=1; i<NumTypes; i++)
		{
			for(int j=0; j<Types.Num(); j++)
			{
				if (TypeCombos.Contains(Types[j]))	// Don't add twice!
					continue;
				TypeCombos.Add(Types[j]);
				break;
			}
		}

		// Did we run out of Types?
		if (TypeCombos.Num() < NumTypes)
			break;

		// Test its effectiveness against all other Types
		bSuccess = true;
		for(const UType* Defender : Types)
		{
			if (Defender->GetModifierWhenAttacked(TypeCombos)<1)
			{
				bSuccess = false;
				FString attackers;
				for(const UType* Attacker : TypeCombos)
					attackers += Attacker->GetName() + " ";
				GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, TEXT("Defender " + Defender->GetName() + " resisted " + attackers));
				break;
			}
		}
		if (bSuccess)
			for (UType* SuccessfulType : TypeCombos)
				NeutralCoverage.Add(SuccessfulType);
	}
}


#pragma endregion