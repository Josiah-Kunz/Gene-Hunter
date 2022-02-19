


#include "Type.h"
#include "GeneHunterBPLibrary.h"

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

	/*
	 *	Visualization of algorithm
	 *	==========================
	 *
	 *		- In this example, there are 10 Types A-J
	 *		- In this example, NumTypes=4
	 *		- The iteration count is boxed on the left
	 *		- E.g., in the zeroth iteration, Types ABCD are tested
	 *
	 *	0 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2 3
	 *
	 *	1 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2   3
	 *
	 *	...
	 *
	 *	6 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1 2             3
	 *
	 *	7 |
	 *	--
	 *		A B C D E F G H I J
	 *		0 1   2 3
	 *
	 *	Penultimate |
	 *	------------
	 *		A B C D E F G H I J
	 *		          0   1 2 3
	 *
	 *	Final |
	 *	------
	 *		A B C D E F G H I J
	 *		            0 1 2 3
	 *
	 */

	// User is being dumb
	if (Types.Num() == 0 || NumTypes < 1 || NumTypes > Types.Num())
		return;

	// Vars
	bool bSuccess;							// Determines if all Types were hit at least neutrally
	TArray<int> Indices = {0};				// The indices of the Types in TypeCombos. E.g., if Fire/Water is being tested, this may be {4, 13} (or whatever).
	TArray<UType*> TypeCombos;				// The combinations being tested
	bool bIterate;							// When iterating in the while loop, this determines if we're still working on iteration
	int i;									// Dummy int
	
	// Initialize Types being tested
	for(i=1; i<NumTypes; i++)
		Indices.Add(Indices[i-1]+1);	// {0, 1, 2, 3}

	// Loop until all options are exhausted
	int Failsafe = 0;
	while (Failsafe < UGeneHunterBPLibrary::MAX_ITERATIONS && Indices[0] <= Types.Num() - NumTypes)
	{

		// Test this combination's effectiveness against all other Types
		TypeCombos.Empty();
		for (i=0; i<NumTypes;i++)
			TypeCombos.Add(Types[Indices[i]]);
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
		
		
		// Iterate
		bIterate = true;
		i=NumTypes-1;
		while (bIterate && i>=0)
		{
			Indices[i]++;
			if (Indices[i] >= Types.Num() - (NumTypes-i))	// i=4's cap is 9; i=3's cap is 8; etc.
			{
				i--;	// Go to the previous index
			} else
			{
				bIterate = false;
				for(int j=i+1; j<NumTypes;j++)	// This i works! Reset its following indices (e.g., if i=2 was validly set to 6, set i=3 to 7 and i=4 to 8)
				{
					Indices[j] = Indices[i]+(j-i);
				}
			}
		}
		if (bIterate)	// Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe++;
	}
}


#pragma endregion