#pragma once
#include "Type.h"

#include <filesystem>
#include <string>

#include "../GeneHunterBPLibrary.h"
#include "AssetRegistry/AssetRegistryModule.h"

#pragma region Public functions

float UType::CombineModifiers(const float A, const float B, const EAttackModifierMode Mode)
{

	switch(Mode)
	{
	case EAttackModifierMode::Coverage:
		return FMath::Max(A, B);
		
	case EAttackModifierMode::MultiType:
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

	default:
		UE_LOG(LogTemp, Error, TEXT("Mode not coded for in Type::CombineModifiers! Fix ASAP!"));
		return 1;
	}
}

float UType::GetAttackModifier(const UType* AgainstType)
{
	if (AttackModifiers.Contains(AgainstType))
		return AttackModifiers[AgainstType].Modifier;
	return 1;
}


TArray<FTypeArray1D*> UType::Analyze(const TArray<UType*>& TypesToAnalyze, const TArray<FTypeArray1D*>& AgainstTypes,
	const FFloatRange Range, const EAttackModifierMode Mode, const bool bAtk, const bool bDebug)
{
	
	TArray<FTypeArray1D*> Ret;
	float OverallModifier = 1;

	// Loop over, e.g., {{Fire, Water}, {Fire, Grass}, {Grass, Water}, ...}
	for(FTypeArray1D* AgainstInfo : AgainstTypes)
	{

		// Debug
		if (bDebug)
			UE_LOG(LogTemp, Display, TEXT("======================="));

		// Rely on another function
		const float Modifier = GetNetModifier(bAtk ? TypesToAnalyze : AgainstInfo->Array,
			bAtk ? AgainstInfo->Array : TypesToAnalyze,
			Mode, bDebug);

		// All done with combining types; add?
		if (Range.Contains(Modifier))
			Ret.Add(AgainstInfo);
		
		
		// Initialize Modifier
		InitializeModifier(OverallModifier, Mode);
	}

	// Return result
	return Ret;
}

float UType::GetNetModifier(const TArray<UType*>& AtkTypes, const TArray<UType*>& DefTypes,
	const EAttackModifierMode Mode, const bool bDebug)
{

	// Set initial modifier
	float Modifier = 1;
	InitializeModifier(Modifier, Mode);

	// Loop over attackers and add their modifiers
	for (UType* Atk : AtkTypes)
	{
		// Squirrel protection
		if (!Atk)
			continue;

		// Get defender names for debug purposes
		FString DefNames = "[";

		// Single attack vs all defense Types (defenders always act as multi-Type)
		float SingleAtkMod = 1;
		for(const UType* Def : DefTypes)
		{
			if (Atk->AttackModifiers.Contains(Def))
			{
				SingleAtkMod = CombineModifiers(SingleAtkMod, Atk->GetAttackModifier(Def));
				DefNames += Def->GetName() + " ";
			} else if (bDebug) {
				UE_LOG(LogTemp, Warning, TEXT("%s does not contain AttackModifiers data on %s!"),
						*Atk->GetName(), *Def->GetName());
				SingleAtkMod = 1;
			}
		}

		// End names list
		DefNames += "]";
		DefNames = DefNames.Replace(TEXT(" ]"), TEXT("]"));
		
		// Best is based on mode
		Modifier = CombineModifiers(Modifier, SingleAtkMod, Mode);

		// Debug
		if (bDebug)
		{
			const FString NewModString = FString::SanitizeFloat(SingleAtkMod);
			const FString TotalModString = FString::SanitizeFloat(Modifier);
			UE_LOG(LogTemp, Display, TEXT("%s attacks %s => %s (Total: %s)"),
						*Atk->GetName(), *DefNames,
						*NewModString, *TotalModString);
		}
	}

	// Return
	return Modifier;
}

float UType::GetNetModifier(const FTypeArray1D AtkTypes, const FTypeArray2D DefTypes, const EAttackModifierMode Mode, const bool bDebug)
{
	return GetNetModifier(AtkTypes.Array, DefTypes.Array, Mode, bDebug);
}


TArray<FTypeArray2D> UType::AnalyzeAll(TArray<UType*>& Types, const int NumTestedTypes, const int NumUntestedTypes,
	const FFloatRange Range, const bool bAnalyzeAtk, const EAttackModifierMode Mode)
{


	/*
	 *	Visualization of algorithm
	 *	==========================
	 *
	 *		- In this example, there are 10 Types A-J
	 *		- In this example, NumTestedTypes=4, NumUntestedTypes=1, Range=[1, open), bAnalyzeAtk=true
	 *		- The iteration count is boxed on the left
	 *		- E.g., in the zeroth iteration, Types ABCD are tested against the "first row" (defender; presumably type A)
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
	
	// The returned variable
	TArray<FTypeArray2D> Analysis;
	
	// User is being dumb
	if (Types.Num() == 0 ||
		NumTestedTypes < 1 || Types.Num() < NumTestedTypes ||
		NumUntestedTypes < 1 || Types.Num() < NumUntestedTypes)
		return Analysis;

	// Vars
	TArray TestedIndices = {0};				// The indices of the Types in TestedTypes. E.g., if Fire/Water is being tested, this may be {4, 13} (or whatever).
	TArray UntestedIndices = {0};			// Same with what's being tested against
	TArray<UType*> TypeCandidates;			// If bAtk, the combination that is defending
	int i;									// Dummy int
	TArray<UType*> AtkTypes, DefTypes;
	float Modifier;							// The result of the (incremental) test
	
	// Initialize Types being tested
	for(i=1; i<NumTestedTypes; i++)
		TestedIndices.Add(TestedIndices[i-1] + 1);	// {0, 1, 2, 3}
	
	// Loop until all options are exhausted
	int Failsafe1 = 0, Failsafe2;
	while (Failsafe1 < UGeneHunterBPLibrary::MAX_ITERATIONS && TestedIndices[0] <= Types.Num() - NumTestedTypes)
	{

		// Get the attacking Type combination based on current indices
		FTypeArray2D A;
		Analysis.Add(A);
		for (i=0; i<NumTestedTypes;i++)
			Analysis.Last().Array.Add(Types[TestedIndices[i]]);
		
		// Reset defending indices (since we're about to iterate over them)
		UntestedIndices = {0};
		for(i=1; i<NumUntestedTypes;i++)
			UntestedIndices.Add(UntestedIndices[i-1]+1);
		
		// Test this combination's effectiveness against all other Types
		Failsafe2 = 0;
		while (Failsafe2 < UGeneHunterBPLibrary::MAX_ITERATIONS && UntestedIndices[0] <= Types.Num() - NumUntestedTypes)
		{

			// Get the attacking Type combination based on indices
			TypeCandidates.Empty();
			for (i=0; i<NumUntestedTypes;i++)
				TypeCandidates.Add(Types[UntestedIndices[i]]);

			// Get the [best] modifier (this is the meat; everything else is just bookkeeping!)
			AtkTypes = bAnalyzeAtk ? Analysis.Last().Array : TypeCandidates;
			DefTypes = bAnalyzeAtk ? TypeCandidates : Analysis.Last().Array;
			Modifier = GetNetModifier(AtkTypes, DefTypes, Mode);
			
			// Check success
			if (Range.Contains(Modifier))
				for (UType* SuccessfulType : TypeCandidates)
					Analysis.Last().Array2.Add(SuccessfulType);
			
			// Iterate
			if (IncrementIndices(Types, UntestedIndices)) // Never able to iterate; must be at the end of all possible Type combinations
				break;
			Failsafe2++;
		}

		// Iterate
		if (IncrementIndices(Types, TestedIndices)) // Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe1++;
	}

	return Analysis;
}

#pragma endregion

/*
void UType::SortTypesAttacking(const TArray<UType*> Types, const int NumAtkTypes, const int NumDefTypes,
	const FFloatRange Range, const EAttackModifierMode Mode, TArray<FTypeArray2D>& Sorted)
{

	// Get unsorted list
	TArray<FTypeArray1D*> Attackers = GetAllTypeCombinations(Types, NumAtkTypes);
	TArray<FTypeArray1D*> Defenders = GetAllTypeCombinations(Types, NumDefTypes);

	// In "Sorted", Array is the attack combinations and TypeArray2D is the defenders
	// For example, using Pokemon rules, some entries could be:
	//	-----------------------------
	//	If multitype:
	//		- Sorted[0].Array = {Fire, Water}
	//		- Sorted[0].TypeArray2D = {Steel, Normal,
	//									Ice, Electric, ...}
	//
	//	If coverage:
	//		- Sorted[0].Array = {Fire, Water}
	//		- Sorted[0].TypeArray2D = {Grass, Normal,		(because Fire alone would suffice)
	//									Fire, Rock, ...}	(because Water alone would suffice)
	Sorted = {};
	for(int i=0; i<Attackers.Num(); i++)
	{

		// Attacking types (Array)
		const TArray<UType*> AtkTypes = Attackers[i]->Array;

		// Defending types that fall within range
		TArray<UType*> DefTypes = {};
		TArray<FTypeArray1D*> AnalysisResult = Analyze(Attackers[i]->Array, Defenders, Range, Mode, true);
		for(FTypeArray1D* TypeInfo : AnalysisResult)
			for(UType* Type : TypeInfo->Array)
				DefTypes.Add(Type);
		
		// Construct and add
		FTypeArray2D TypeInfo = FTypeArray2D{AtkTypes, DefTypes};
		Sorted.Add(TypeInfo);
	}

	// Sort based on number of DefTypes
	Sorted.Sort([Range, Defenders, Mode](const FTypeArray1D& A, const FTypeArray1D& B)
	{

		// Get number of advantages (or whatever based on Range)
		int NumA = A.Array.Num();
		int NumB = B.Array.Num();

		// If they're equal, sort "ThenBy"
		if (NumA == NumB)
		{

			// Get "inverted" range for tiebreaker
			FFloatRange InverseRange;
			
			// If getting "resisted" Types, tiebreaker is "badness" (least number of advantages)
			if (Range.GetLowerBound().GetValue() < 1)
				InverseRange = FFloatRange{
				FFloatRangeBound::Exclusive(Range.GetUpperBound().GetValue()),
				FFloatRangeBound::Open()
				};
			else 
				// If getting "effective" Types, tiebreaker is "goodness" (least number of resisted Types)
				InverseRange = FFloatRange{
			FFloatRangeBound::Open(),
			FFloatRangeBound::Exclusive(Range.GetLowerBound().GetValue())
				};

			// Make decision
			NumA = Analyze(A.Array, Defenders, InverseRange, Mode, true).Num();
			NumB = Analyze(B.Array, Defenders, InverseRange, Mode, true).Num();
			return NumA < NumB;
		}
		
		// Not equal; return as usual
		return NumA > NumB;
	});
}
*/

#pragma region Getting Types

void UType::GetAllTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC)
{
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(TEXT("Type"), TypeAssets, false);
	if (bSortABC)
		UGeneHunterBPLibrary::SortAssetsAlphabetically(TypeAssets, TypeAssets);
}

void UType::GetAllTypes(TArray<UType*>& Types, const TArray<UType*> Exclude, const bool bSortABC)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllTypeAssets(Assets, bSortABC);
	for(FAssetData& Asset : Assets)
	{
		if (UType* Type = Cast<UType>(Asset.GetAsset()))
		{
			if (!Exclude.Contains(Type))
				Types.Add(Type);
		}
	}
}

void UType::GetAllTypes(TArray<UType*>& Types, const bool bSortABC)
{
	GetAllTypes(Types, {}, bSortABC);
}

TArray<FTypeArray1D*> UType::GetAllTypeCombinations(const TArray<UType*>& Types, const int NumTypes)
{

	TArray<FTypeArray1D*> Ret = {};
	
	// User is being dumb
	if (Types.Num() == 0 || NumTypes < 1 || Types.Num() < NumTypes)
		return Ret;

	// Setup trackers
	TArray Indices = {0};
	for(int i=1; i<NumTypes; i++)
		Indices.Add(Indices[i-1] + 1);

	// Loop until options are exhausted
	int Failsafe = 0;
	while (Failsafe < UGeneHunterBPLibrary::MAX_ITERATIONS && Indices[0] <= Types.Num() - NumTypes)
	{

		// Populate TypeInfo
		FTypeArray1D* TypeInfo = new FTypeArray1D{{}};
		for (int i=0; i<NumTypes;i++)
			TypeInfo->Array.Add(Types[Indices[i]]);

		// Add newest entry
		Ret.Add(TypeInfo);
		
		// Iterate
		if (IncrementIndices(Types, Indices)) // Never able to iterate; must be at the end of all possible Type combinations
			break;
		Failsafe++;
	}

	// Return
	return Ret;
	
}

void UType::PruneTypeAttackMods(UType* Type)
{

	// Vars
	TMap OldMap(Type->AttackModifiers);

	// Clear and refill map
	Type->AttackModifiers.Empty();
	for(const TPair<UType*, FAttackModifier>& pair : OldMap)
	{
		if (pair.Key != nullptr)
			Type->AttackModifiers.Add(pair.Key, pair.Value);
	}
}

#pragma endregion

#pragma region Private functions

TArray<UType*> UType::GetAllTypesFromSeeds(TArray<UType*> TypesSeeds)
{
	TArray<UType*> Ret;
	for(UType* Type : TypesSeeds)
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

bool UType::IncrementIndices(const TArray<UType*>& Types, TArray<int>& Indices)
{

	/*
	 *	In this example, we have five types and three indices:
	 *		Indices = {1, 2, 5}
	 *		Types.Num() ==> 5
	 */
	
	bool Ret = true;
	int i=Indices.Num()-1;	// Start at the last index (e.g., the "5" in {1, 2, 5})
	while (Ret && i>=0)
	{
		Indices[i]++;		// Increment this index (e.g., the "5" becomes a "6", which is over cap)
		if (Indices[i] >= Types.Num() - ((Indices.Num()-1)-i))	// i=2's cap is 5; i=1's cap is 4; etc.
			{
			i--;			// Go to the previous index (e.g, the "2")
			} else
			{
				Ret = false;
				for(int j=i+1; j<Indices.Num();j++)	// This i works! Reset its following Indices (e.g., if i=1 was validly set to "3", set i=2 to "4")
					Indices[j] = Indices[i]+(j-i);
			}
	}
	return Ret;
}

void UType::InitializeModifier(float& Modifier, const EAttackModifierMode Mode)
{
	switch (Mode)
	{
	case EAttackModifierMode::MultiType:

		// Get the [best] modifier
		Modifier = 1;
		break;
	case EAttackModifierMode::Coverage:

		// Get the [net] modifier
		Modifier = -INFINITY;
		break;
	default:
		UE_LOG(LogTemp, Error, TEXT("Mode not coded for in Type::InitializeModifier! Fix ASAP!"));
	}
}

#pragma endregion