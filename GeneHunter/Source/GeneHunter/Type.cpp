


#include "Type.h"
#include "GeneHunterBPLibrary.h"

float UType::CombineModifiers(const float A, const float B)
{
	// Order doesn't matter
	float Min, Max;
	if (A>B)
	{
		Max = A;
		Min = B;
	} else
	{
		Max = B;
		Min = A;
	}

	// Apply regular multiplicative rules
	if (Min >= 0)			 
		return Min*Max;

	// If healed and weak to...
	if (Max > 1)
		return Min/Max;  // e.g., -1 & 2 -> -1/2

	// Healing trumps all other damage reduction
	return Min;
	
}

TArray<UType*> UType::AnalyzeAtk(const TArray<UType*> AtkTypes, const float Min, const float Max, const bool Inclusive, const EAttackModifierMode Mode)
{
	TArray<UType*> Ret;
	TArray<UType*> DefTypes = GetAllTypes(AtkTypes);
	float Modifier;
	for(UType* Def : DefTypes)
	{
		switch (Mode)
		{
		case EAttackModifierMode::MultiType:
			Modifier = 1;
			break;
		case EAttackModifierMode::Coverage:
			Modifier = -INFINITY;
			break;
		}
		for(UType* Atk : AtkTypes)
		{
			switch (Mode)
			{
			case EAttackModifierMode::MultiType:
				Modifier = CombineModifiers(Modifier, Atk->AttackModifiers[Def].Modifier);
				break;
			case EAttackModifierMode::Coverage:
				Modifier = FMath::Max(Modifier, Atk->AttackModifiers[Def].Modifier);
				break;
			}
		}
		if (InRange(Modifier, Min, Max, Inclusive))
			Ret.Add(Def);
	}
	return Ret;
}

bool UType::InRange(const float Float, const float Min, const float Max, const bool Inclusive)
{
	return Inclusive && Min <= Float && Float <= Max || !Inclusive && Min<Float && Float<Max;
}


TArray<UType*> UType::GetAllTypes(TArray<UType*> PossibleTypes)
{
	TArray<UType*> Ret;
	for(UType* Type : PossibleTypes)
	{
		if (Type)
		{
			for(TTuple<UType*, FAttackModifier>& Kvp : Type->AttackModifiers)
				Ret.Add(Kvp.Key);
			break;
		}
	}
	return Ret;
}


#pragma region Getting modifiers when attacking

/*
TArray<UType*> UType::GetMultiAtkTypes(const TArray<UType*> AtkTypes, TArray<UType*> DefTypes, const float Min, const float Max, const bool Inclusive)
{

	// If DefTypes is not given, assume AtkTypes contains the correct AtkModifiers
	if (DefTypes.Num() == 0)
	{
		for(UType* Atk : AtkTypes)
		{
			if (Atk)
			{
				Atk->AttackModifiers.GetKeys(DefTypes);
				break;
			}
		}
	}
	
	TArray<UType*> Ret;
	float Modifier;
	for(UType* Defender : DefTypes)
	{
		if (Defender)
		{
			Modifier = 1;
			for(UType* Attacker : AtkTypes)
			{
				if (Attacker)
					Modifier = CombineModifiers(Modifier, Attacker->AttackModifiers[Defender].Modifier);
			}
			if (Inclusive)
			{
				if (Min <= Modifier && Modifier <= Max)
					Ret.Add(Defender);
			} else
			{
				if (Min < Modifier && Modifier < Max)
					Ret.Add(Defender);
			}
		}
	}
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
}*/


#pragma endregion

#pragma region Sorting for debug purposes

void UType::SortTypesAttacking(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	/*Sorted.Sort([Min, Max, Inclusive](const UType& A, const UType& B)
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
	});*/
}

void UType::SortTypesDefending(const TArray<UType*> Types, TArray<UType*>& Sorted, const float Min, const float Max, const bool Inclusive)
{
	Sorted = Types;
	/*Sorted.Sort([Min, Max, Inclusive](const UType& A, const UType& B)
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
	});*/
}

void UType::SortTypesAttackingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted)
{
	Sorted = Types;
	/*Sorted.Sort([](const UType&A, const UType& B)
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
		const float RatioA = EffectiveA/static_cast<float>(IneffectiveA);
		const float RatioB = EffectiveB/static_cast<float>(IneffectiveB);
		
		// If equal, defer to the one whose numerator is bigger
		if (FMath::IsNearlyEqual(RatioA, RatioB))
			return EffectiveA > EffectiveB;

		// Judge accordingly
		return  RatioA > RatioB ;
	});*/
}

void UType::SortTypesDefendingRatio(const TArray<UType*> Types, TArray<UType*>& Sorted)
{
	Sorted = Types;
	/*Sorted.Sort([](const UType&A, const UType& B)
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
		const float RatioA = ResistedA/static_cast<float>(WeakToA);
		const float RatioB = ResistedB/static_cast<float>(WeakToB);
		
		// If equal, defer to the one whose numerator is bigger
		if (FMath::IsNearlyEqual(RatioA, RatioB))
			return ResistedA > ResistedB;

		// Judge accordingly
		return  RatioA > RatioB ;
	});*/
}

void UType::GetCoverage(const TArray<UType*> Types, TArray<UType*>& Coverage, const int NumAtkTypes, const int NumDefTypes)
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
	if (Types.Num() == 0 ||
		NumAtkTypes < 1 || Types.Num() < NumAtkTypes ||
		NumDefTypes < 1 || Types.Num() < NumDefTypes)
		return;

	// Vars
	bool bSuccess;							// Determines if all Types were hit at least neutrally
	TArray<int> AtkIndices = {0};			// The indices of the Types in AtkTypes. E.g., if Fire/Water is being tested, this may be {4, 13} (or whatever).
	TArray<int> DefIndices = {0};			// Same with defenders
	TArray<UType*> AtkTypes;				// The combination that is attacking
	TArray<UType*> DefTypes;				// The combination that is defending
	int i;									// Dummy ints
	float Modifier;
	
	// Initialize Types being tested
	for(i=1; i<NumAtkTypes; i++)
		AtkIndices.Add(AtkIndices[i-1] + 1);	// {0, 1, 2, 3}

	// Loop until all options are exhausted
	int Failsafe1 = 0, Failsafe2;
	while (Failsafe1 < UGeneHunterBPLibrary::MAX_ITERATIONS && AtkIndices[0] <= Types.Num() - NumAtkTypes)
	{

		// Get the attacking Type combination based on indices
		AtkTypes.Empty();
		for (i=0; i<NumAtkTypes;i++)
			AtkTypes.Add(Types[AtkIndices[i]]);

		// Reset defending indices
		DefIndices = {0};
		for(i=1; i<NumDefTypes;i++)
			DefIndices.Add(DefIndices[i-1]+1);
		
		// Test this combination's effectiveness against all other Types
		bSuccess = true;
		Failsafe2 = 0;
		while (Failsafe2 < UGeneHunterBPLibrary::MAX_ITERATIONS && DefIndices[0] <= Types.Num() - NumDefTypes)
		{

			// Get the attacking Type combination based on indices
			DefTypes.Empty();
			for (i=0; i<NumDefTypes;i++)
				DefTypes.Add(Types[DefIndices[i]]);
			//Modifier = GetNetModifier(AtkTypes, DefTypes, ModifierFetchMode::Max);
			Modifier = 1;
			
			FString attackers, defenders;
			for(auto& Atks :AtkTypes)
				attackers += Atks->GetName() + " ";
			for(auto& Defs :DefTypes)
				defenders += Defs->GetName() + " ";
			FString logmsg = TEXT("[" + attackers + "] vs [" + defenders + "] = " + FString::SanitizeFloat(Modifier));
			GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, logmsg);
			UE_LOG(LogBlueprint, Warning, TEXT("%s"), *logmsg);
			
			if (Modifier < 1)
			{
				bSuccess = false;
				break;
			}
			
			// Iterate
			if (IncrementIndices(Types, DefIndices)) // Never able to iterate; must be at the end of all possible Type combinations
				break;
			Failsafe2++;
		}
		if (bSuccess)
				for (UType* SuccessfulType : AtkTypes)
				Coverage.Add(SuccessfulType);
		
		
		// Iterate
		if (IncrementIndices(Types, AtkIndices)) // Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe1++;
	}
}

bool UType::IncrementIndices(const TArray<UType*> Types, TArray<int>& Indices)
{
	bool Ret = true;
	int i=Indices.Num()-1, j;
	while (Ret && i>=0)
	{
		Indices[i]++;
		if (Indices[i] >= Types.Num() - (Indices.Num()-i))	// i=4's cap is 9; i=3's cap is 8; etc.
		{
			i--;	// Go to the previous index
		} else
		{
			Ret = false;
			for(j=i+1; j<Indices.Num();j++)	// This i works! Reset its following Indices (e.g., if i=2 was validly set to 6, set i=3 to 7 and i=4 to 8)
				Indices[j] = Indices[i]+(j-i);
		}
	}
	return Ret;
}



#pragma endregion