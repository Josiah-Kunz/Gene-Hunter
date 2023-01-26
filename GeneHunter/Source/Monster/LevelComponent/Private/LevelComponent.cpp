#include "LevelComponent.h"

#include "MathUtil.h"

#pragma region Standard stuff

// Sets default values for this component's properties
ULevelComponent::ULevelComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

#pragma endregion

#pragma region Exp yield

int ULevelComponent::GetBaseExpYield() 
{
	float Ret = BaseExpYield;
	return Ret;
}

void ULevelComponent::SetBaseExpYield(int NewBaseExpYield)
{
	//ExecuteBeforeSetBaseExpYield(GetBaseExpYield(), NewBaseExpYield);
	BaseExpYield = NewBaseExpYield;
	//ExecuteAfterSetBaseExpYield(GetBaseExpYield(), NewBaseExpYield);
}


float ULevelComponent::GetExpYield(ULevelComponent* VictoriousMonster)
{

	// Get level difference. If the enemy is lower level, they get more exp for defeating this Monster.
	int LevelDiff = GetLevel() - VictoriousMonster->GetLevel();
	LevelDiff = FMath::Max(0, LevelDiff); // Ensures positive
	LevelDiff = FMath::Min(10, LevelDiff); // Cap benefits at +10 levels

	// Return based on formula
	float Yield =

		// Base
		BaseExpYield

		// Curve based on the defeated Monster's current level
		* GetTotalLevelExp() / (0.7f + 0.2f * GetLevel() + FMathf::Pow(0.00006*GetLevel(), 3))

		// Reward for "punching up" and defeating a Monster bigger than you
		* FMathf::Pow(1.5f, FMath::Floor((LevelDiff/2.0f)))
	;

	// Delegates
	//ExecuteBeforeGetExpYield(VictoriousMonster, Yield);
	//ExecuteAfterGetExpYield(VictoriousMonster, Yield);

	// Return
	return Yield;
}

#pragma endregion

#pragma region Exp

int ULevelComponent::GetCumulativeExp()
{
	//ExecuteBeforeGetCumulativeExp(CumulativeExp);
	//ExecuteAfterGetCumulativeExp(CumulativeExp);
	return CumulativeExp;
}

void ULevelComponent::SetCumulativeExp(int NewCumulativeExp)
{
	// Delegate
	//ExecuteBeforeSetCumulativeExp(GetCumulativeExp(), NewCumulativeExp);
	//SetCumulativeExpOutlet.ExecuteBefore(GetCumulativeExp(), NewCumulativeExp);
	
	// Cache old (it's a surprise tool that will help us later!)
	const int OldCEXP = CumulativeExp;

	// Set and clamp exp
	CumulativeExp = FMath::Clamp(NewCumulativeExp, 1, GetMaxExp());

	// Clamp level
	int NewLevel = GetLevel();
	if (NewLevel < MinLevel())
	{
		NewLevel = MinLevel();
		CumulativeExp = GetCumulativeExpFromLevel(MinLevel());
	}
	if (NewLevel > MaxLevel())
	{
		NewLevel = MaxLevel();
		CumulativeExp = GetCumulativeExpFromLevel(MaxLevel());
	}

	// Delegate
	//ExecuteAfterSetCumulativeExp(OldCEXP, CumulativeExp);
	for(FSetCumulativeExpOutlet Outlet : AfterSetCumulativeExp)
		Outlet.SetCumulativeExpDelegate.ExecuteIfBound(GetCumulativeExp(), CumulativeExp);
	CumulativeExp = NewCumulativeExp;
}

void ULevelComponent::AddExp(int AddedCumulativeExp)
{
	//ExecuteBeforeAddExp(GetCumulativeExp(), AddedCumulativeExp);
	SetCumulativeExp(GetCumulativeExp() + AddedCumulativeExp);
	//ExecuteAfterAddExp(GetCumulativeExp(), AddedCumulativeExp);
}

#pragma endregion

#pragma region Level

int ULevelComponent::GetLevel() 
{
	return GetLevelFromCXP(GetCumulativeExp());
}

int ULevelComponent::GetLevelFromCXP(const int CXP)
{
	return FMath::Floor(FMathf::Pow(CXP, 1/ExpExponent()));
}

void ULevelComponent::SetLevel(int NewLevel)
{
	//ExecuteBeforeSetLevel(GetLevel(), NewLevel);
	const int Level = FMathf::Clamp(NewLevel, MinLevel(), MaxLevel());
	SetCumulativeExp(GetCumulativeExpFromLevel(Level));
	//ExecuteAfterSetLevel(GetLevel(), NewLevel);
}

void ULevelComponent::AddLevels(const int AddedLevels)
{
	SetLevel(GetLevel() + AddedLevels);
}

int ULevelComponent::MaxLevel()
{
	int MaxLevel = 100;
	//ExecuteBeforeMaxLevel(MaxLevel);
	//ExecuteAfterMaxLevel(MaxLevel);
	return MaxLevel;
}

int ULevelComponent::MinLevel()
{
	int MinLevel = 1;
	//ExecuteBeforeMinLevel(MinLevel);
	//ExecuteAfterMinLevel(MinLevel);
	return MinLevel;
}

#pragma endregion

#pragma region Conversion: exp <-> level

float ULevelComponent::ExpExponent()
{
	return 3;
}

float ULevelComponent::GetCumulativeExpFromLevel(const int TargetLevel)
{
	return FMathf::Pow(TargetLevel, ExpExponent());
}

float ULevelComponent::GetExpToLevel()
{
	if (GetLevel() == MaxLevel())
		return 0;
	const float NextLevelExp = GetCumulativeExpFromLevel(GetLevel() + 1);
	return NextLevelExp - GetLevelExp();
}

float ULevelComponent::GetTotalLevelExp()
{
	if (GetLevel() == MaxLevel())
		return 0;
	const float ThisLevelExp = GetCumulativeExpFromLevel(GetLevel());
	const float NextLevelExp = GetCumulativeExpFromLevel(GetLevel() + 1);
	return NextLevelExp - ThisLevelExp;
}

float ULevelComponent::GetLevelExp()
{
	return GetCumulativeExp() - GetCumulativeExpFromLevel(GetLevel());
}

float ULevelComponent::GetMaxExp()
{
	return GetCumulativeExpFromLevel(MaxLevel());
}

#pragma endregion
