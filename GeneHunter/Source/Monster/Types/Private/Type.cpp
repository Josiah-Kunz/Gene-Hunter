#pragma once
#include "Type.h"
#include <algorithm>

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
				SingleAtkMod = UType::CombineModifiers(SingleAtkMod, Atk->GetAttackModifier(Def));
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
		Modifier = UType::CombineModifiers(Modifier, SingleAtkMod, Mode);

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

#pragma region Getting Types

void UType::GetAllTypeAssets(TArray<FAssetData>& TypeAssets, const bool bSortABC,
	const bool bIncludeDummy, const bool bIncludeReal)
{

	// Get the assets
	const FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");
	AssetRegistryModule.Get().GetAssetsByClass(TEXT("Type"), TypeAssets, false);

	// Remove dummies or reals
	for(int i=TypeAssets.Num() - 1; i>=0; i--)
	{
		const bool bIsDummy = TypeAssets[i].AssetName.ToString().Contains(DUMMY_IDENTIFIER);
		if (!bIncludeDummy && bIsDummy)
		{
			TypeAssets.RemoveAt(i);
			continue;
		}

		if (!bIncludeReal && !bIsDummy)
		{
			TypeAssets.RemoveAt(i);
			continue;
		}
	}

	// Sort
	if (bSortABC)
		UAssetFunctionLibrary::SortAssetsAlphabetically(TypeAssets, TypeAssets);
}

void UType::GetAllTypes(TArray<UType*>& Types, const bool bSortABC, const bool bDummyTypes)
{
	GetAllTypes(Types, {}, bSortABC, bDummyTypes);
}

void UType::GetAllTypes(TArray<UType*>& Types, const TArray<UType*>& Exclude, const bool bSortABC,
	const bool bDummyTypes)
{
	Types.Empty();
	TArray<FAssetData> Assets;
	GetAllTypeAssets(Assets, bSortABC, bDummyTypes, !bDummyTypes);
	for(FAssetData& Asset : Assets)
	{

		// Check cast
		if (UType* Type = Cast<UType>(Asset.GetAsset()))
		{

			// Check exclusions, nullptr
			if (Type == nullptr || Exclude.Contains(Type))
				continue;

			// Dummy or nah?
			if (bDummyTypes)
			{
				if (Type->GetName().Contains(DUMMY_IDENTIFIER))
					Types.Add(Type);
			} else
			{
				Types.Add(Type);
			}
		}
	}
}

UType* UType::GetTypeByName(const TArray<UType*>& Pool, const FName Name)
{
	for(UType* Type : Pool)
		if (Type->GetFName() == Name)
			return Type;
	return nullptr;
}


void UType::GetTypesInRange(const TArray<UType*>& AllTypes, const FFloatRange Range, TArray<UType*>& Defenders)
{
	Defenders = {};
	for(UType* Defender : AllTypes)
		if (Range.Contains(GetAttackModifier(Defender)))
			Defenders.Add(Defender);
}

void UType::GetTypesInRangeDefending(const TArray<UType*>& AllTypes, const FFloatRange Range, TArray<UType*>& Attackers)
{
	Attackers = {};
	for(UType* Attacker : AllTypes)
		if (Range.Contains(Attacker->GetAttackModifier(this)))
			Attackers.Add(Attacker);
}



#pragma endregion

#pragma region Utilities

bool UType::ArraysAreEqual(const TArray<UType*>& Actual, const TArray<UType*>& Expected, FString& Description)
{

	// Start building string in case it fails
	Description += "[Expected: ";

	// Expected
	for(const UType* ExpectedType : Expected)
		if (ExpectedType)
			Description += ExpectedType->GetName() + " ";

	// Actual
	Description += " || Actual: ";
	for(const UType* ActualType : Actual)
		if (ActualType)
			Description += ActualType->GetName() + " ";

	// Delete last space
	Description += "]";
	Description = Description.Replace(TEXT(" ]"), TEXT("] "));

	// Can't simply TestSame; TestSame([A, B], [B, A]) fails!
	bool bPass = Actual.Num() == Expected.Num();
	if (bPass)
	{
		for(const UType* ExpectedType : Expected)
		{
			if (!Contains(Actual, ExpectedType))
			{
				if (ExpectedType == nullptr)
				{
					UE_LOG(LogTemp, Warning, TEXT("ExpectedType is null in UType::ArraysAreEqual. Surely this is a bug."))
					return false;
				}
				Description += " | Expected [" + ExpectedType->GetName() + "] not found!";
				bPass = false;
			}
		}
	} else
	{
		Description += " " + FString::SanitizeFloat(Actual.Num()) + " != " + FString::SanitizeFloat(Expected.Num());
	}
	return bPass;
	
}

FString UType::ArrayToFString(const TArray<UType*>& Array)
{
	FString Ret = "[";
	for(const UType* Type : Array)
	{
		if (Type == nullptr || !IsValid(Type))
			Ret += "NULLPTR, ";
		else
			Ret += Type->GetName() + ", ";
	}
	Ret += "]";
	Ret = Ret.Replace(TEXT(", ]"), TEXT("]"));
	return Ret;
}

bool UType::Contains(const TArray<UType*>& Container, const UType* SearchTarget,
									  const bool bByName)
{
	return std::any_of(std::begin(Container), std::end(Container),
								[&](const UType* Test) {
\
									// Guards
									if (Test == nullptr)
									{
										UE_LOG(LogTemp, Warning, TEXT("Container element is nullptr in UType::Contains. Surely this is a bug."))
										return false;
									}
									if (SearchTarget == nullptr)
									{
										UE_LOG(LogTemp, Warning, TEXT("Search Type is nullptr in UType::Contains. Surely this is a bug."))
										return false;
									}
									
									// Actual check
									if (bByName)
										return Test->GetName() == SearchTarget->GetName();
									return Test == SearchTarget;
								});
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

#pragma endregion