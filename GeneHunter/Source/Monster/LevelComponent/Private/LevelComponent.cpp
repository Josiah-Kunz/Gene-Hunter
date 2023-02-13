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

float ULevelComponent::GetBaseExpYield() 
{
	// Get original for delegates
	const float OriginalBaseExpYield = BaseExpYield;

	// Set up the modifiable return value
	float ReturnedBaseExpYield = BaseExpYield;

	// Call before/after delegates
	GetBaseExpYieldOutlet.ExecuteBefore(OriginalBaseExpYield, ReturnedBaseExpYield);
	GetBaseExpYieldOutlet.ExecuteAfter(OriginalBaseExpYield, ReturnedBaseExpYield);
	
	// Return for use in other functions
	return ReturnedBaseExpYield;
}

void ULevelComponent::SetBaseExpYield(float NewBaseExpYield)
{

	// Get outlet values
	const float OriginalBaseExpYield = GetBaseExpYield();
	const float InputBaseExpYield = NewBaseExpYield;

	// Call + execute + call
	SetBaseExpYieldOutlet.ExecuteBefore(OriginalBaseExpYield, InputBaseExpYield, NewBaseExpYield);
	BaseExpYield = NewBaseExpYield;
	SetBaseExpYieldOutlet.ExecuteAfter(OriginalBaseExpYield, InputBaseExpYield, GetBaseExpYield());
}


float ULevelComponent::GetExpYield(ULevelComponent* VictoriousMonster)
{

	// Get level difference. If the enemy is lower level, they get more exp for defeating this Monster.
	uint16 LevelDiff = GetLevel() - VictoriousMonster->GetLevel();
	LevelDiff = FMath::Max(static_cast<uint16>(0), LevelDiff); // Ensures positive
	LevelDiff = FMath::Min(static_cast<uint16>(10), LevelDiff); // Cap benefits at +10 levels

	// Return based on formula
	float ReturnedYield =

		// Base
		BaseExpYield

		// Curve based on the defeated Monster's current level
		* GetTotalLevelExp() / (0.7f + 0.2f * GetLevel() + FMathf::Pow(0.00006*GetLevel(), 3))

		// Reward for "punching up" and defeating a Monster bigger than you
		* FMathf::Pow(1.5f, FMath::Floor((LevelDiff/2.0f)))
	;

	// Cache for delegates
	const float OriginalYield = ReturnedYield;

	// Delegates
	GetExpYieldOutlet.ExecuteBefore(OriginalYield, ReturnedYield, GetLevel(), VictoriousMonster->GetLevel());
	GetExpYieldOutlet.ExecuteAfter(OriginalYield, ReturnedYield, GetLevel(), VictoriousMonster->GetLevel());

	// Return
	return ReturnedYield;
}

#pragma endregion

#pragma region Exp

int32 ULevelComponent::GetCXP()
{

	// Cache for delegates
	const int32 OriginalCXP = CumulativeExp;
	int32 ReturnedCXP;

	// Delegates
	GetCXPOutlet.ExecuteBefore(OriginalCXP, ReturnedCXP);
	GetCXPOutlet.ExecuteAfter(OriginalCXP, ReturnedCXP);

	// Return
	return ReturnedCXP;
}

void ULevelComponent::SetCXP(int32 NewCumulativeExp)
{
	
	// Cache old (for the delegates)
	const uint32 OldCXP = CumulativeExp;
	const int32 InputCXP = NewCumulativeExp;

	// Delegate
	SetCXPOutlet.ExecuteBefore(OldCXP, InputCXP, NewCumulativeExp);

	// Set and clamp exp
	CumulativeExp = FMath::Clamp(NewCumulativeExp, 1, GetMaxExp());

	// Clamp level
	uint16 NewLevel = GetLevel();
	if (NewLevel < GetMinLevel())
	{
		NewLevel = GetMinLevel();
		CumulativeExp = GetCXPFromLevel(GetMinLevel());
	}
	if (NewLevel > GetMaxLevel())
	{
		NewLevel = GetMaxLevel();
		CumulativeExp = GetCXPFromLevel(GetMaxLevel());
	}

	// Set new exp for delegates
	const uint32 NewCXP = GetCXP();

	// Call after delegates
	SetCXPOutlet.ExecuteAfter(OldCXP, InputCXP, NewCXP);
}

void ULevelComponent::AddExp(const int32 AddedCumulativeExp)
{
	SetCXP(GetCXP() + AddedCumulativeExp);
}

#pragma endregion

#pragma region Level

int32 ULevelComponent::GetLevel() 
{
	return GetLevelFromCXP(GetCXP());
}

int32 ULevelComponent::GetLevelFromCXP(const int32 CXP)
{
	return FMath::Floor(FMathf::Pow(CXP, 1/ExpExponent()));
}

void ULevelComponent::SetLevel(int32 NewLevel)
{
	//ExecuteBeforeSetLevel(GetLevel(), NewLevel);
	const uint16 Level = FMathf::Clamp(NewLevel, GetMinLevel(), GetMaxLevel());
	SetCXP(GetCXPFromLevel(Level));
	//ExecuteAfterSetLevel(GetLevel(), NewLevel);
}

void ULevelComponent::AddLevels(const int32 AddedLevels)
{
	SetLevel(GetLevel() + AddedLevels);
}

int32 ULevelComponent::GetMaxLevel()
{
	constexpr uint16 DefaultMaxLevel = 100;
	int32 ReturnedMax = DefaultMaxLevel;
	GetMaxLevelOutlet.ExecuteBefore(DefaultMaxLevel, ReturnedMax);
	GetMaxLevelOutlet.ExecuteAfter(DefaultMaxLevel, ReturnedMax);
	return ReturnedMax;
}

int32 ULevelComponent::GetMinLevel()
{
	constexpr uint16 DefaultMinLevel = 1;
	int32 ReturnedMin = DefaultMinLevel;
	GetMinLevelOutlet.ExecuteBefore(DefaultMinLevel, ReturnedMin);
	GetMinLevelOutlet.ExecuteAfter(DefaultMinLevel, ReturnedMin);
	return ReturnedMin;
}

#pragma endregion

#pragma region Conversion: exp <-> level

float ULevelComponent::ExpExponent()
{
	return 3;
}

int32 ULevelComponent::GetCXPFromLevel(const int32 TargetLevel)
{
	return FMathf::Pow(TargetLevel, ExpExponent());
}

int32 ULevelComponent::GetExpToLevel()
{
	if (GetLevel() == GetMaxLevel())
		return 0;
	const float NextLevelExp = GetCXPFromLevel(GetLevel() + 1);
	return NextLevelExp - GetLevelExp();
}

int32 ULevelComponent::GetTotalLevelExp()
{
	if (GetLevel() == GetMaxLevel())
		return 0;
	const float ThisLevelExp = GetCXPFromLevel(GetLevel());
	const float NextLevelExp = GetCXPFromLevel(GetLevel() + 1);
	return NextLevelExp - ThisLevelExp;
}

int32 ULevelComponent::GetLevelExp()
{
	return GetCXP() - GetCXPFromLevel(GetLevel());
}

int32 ULevelComponent::GetMaxExp()
{
	return GetCXPFromLevel(GetMaxLevel());
}

#pragma endregion
