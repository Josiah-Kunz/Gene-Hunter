#include "StatsComponent.h"

#include "MathUtil.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UStatsComponent::UStatsComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	RandomizeStats();
}

// Called when the game starts
void UStatsComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

#pragma endregion

#pragma region Exp yield

int UStatsComponent::GetBaseExpYield() 
{
	ExecuteBeforeGetBaseExpYield(BaseExpYield);
	ExecuteAfterGetBaseExpYield(BaseExpYield);
	return BaseExpYield;
}

void UStatsComponent::SetBaseExpYield(int NewBaseExpYield)
{
	ExecuteBeforeSetBaseExpYield(GetBaseExpYield(), NewBaseExpYield);
	BaseExpYield = NewBaseExpYield;
	ExecuteAfterSetBaseExpYield(GetBaseExpYield(), NewBaseExpYield);
}


float UStatsComponent::GetExpYield(UStatsComponent* VictoriousMonster)
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
	ExecuteBeforeGetExpYield(VictoriousMonster, Yield);
	ExecuteAfterGetExpYield(VictoriousMonster, Yield);

	// Return
	return Yield;
}

#pragma endregion

#pragma region Exp

int UStatsComponent::GetCumulativeExp()
{
	ExecuteBeforeGetCumulativeExp(CumulativeExp);
	ExecuteAfterGetCumulativeExp(CumulativeExp);
	return CumulativeExp;
}

void UStatsComponent::SetCumulativeExp(int NewCumulativeExp)
{

	// Delegate
	ExecuteBeforeSetCumulativeExp(GetCumulativeExp(), NewCumulativeExp);
	
	// Cache old (it's a surprise tool that will help us later!)
	const int OldLevel = GetLevel();

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

	// Did it change?
	if (NewLevel != OldLevel)
		RecalculateStats();

	// Delegate
	ExecuteAfterSetCumulativeExp(GetCumulativeExp(), NewCumulativeExp);
}

void UStatsComponent::AddExp(int AddedCumulativeExp)
{
	ExecuteBeforeAddExp(GetCumulativeExp(), AddedCumulativeExp);
	SetCumulativeExp(GetCumulativeExp() + AddedCumulativeExp);
	ExecuteAfterAddExp(GetCumulativeExp(), AddedCumulativeExp);
}

#pragma endregion

#pragma region Level

int UStatsComponent::GetLevel() 
{
	return FMath::Floor(FMathf::Pow(GetCumulativeExp(), 1/ExpExponent()));
}

void UStatsComponent::SetLevel(int NewLevel)
{
	ExecuteBeforeSetLevel(GetLevel(), NewLevel);
	const int Level = FMathf::Clamp(NewLevel, MinLevel(), MaxLevel());
	SetCumulativeExp(GetCumulativeExpFromLevel(Level));
	for(FStat* Stat : StatsArray)
		Stat->Update(GetLevel());
	ExecuteAfterSetLevel(GetLevel(), NewLevel);
}

void UStatsComponent::AddLevels(const int AddedLevels)
{
	SetLevel(GetLevel() + AddedLevels);
}

int UStatsComponent::MaxLevel()
{
	int MaxLevel = 100;
	ExecuteBeforeMaxLevel(MaxLevel);
	ExecuteAfterMaxLevel(MaxLevel);
	return MaxLevel;
}

int UStatsComponent::MinLevel()
{
	int MinLevel = 1;
	ExecuteBeforeMinLevel(MinLevel);
	ExecuteAfterMinLevel(MinLevel);
	return MinLevel;
}

#pragma endregion

#pragma region Conversion: exp <-> level

float UStatsComponent::ExpExponent()
{
	return 3;
}

float UStatsComponent::GetCumulativeExpFromLevel(const int TargetLevel)
{
	return FMathf::Pow(TargetLevel, ExpExponent());
}

float UStatsComponent::GetExpToLevel()
{
	if (GetLevel() == MaxLevel())
		return 0;
	const float NextLevelExp = GetCumulativeExpFromLevel(GetLevel() + 1);
	return NextLevelExp - GetLevelExp();
}

float UStatsComponent::GetTotalLevelExp()
{
	if (GetLevel() == MaxLevel())
		return 0;
	const float ThisLevelExp = GetCumulativeExpFromLevel(GetLevel());
	const float NextLevelExp = GetCumulativeExpFromLevel(GetLevel() + 1);
	return NextLevelExp - ThisLevelExp;
}

float UStatsComponent::GetLevelExp()
{
	return GetCumulativeExp() - GetCumulativeExpFromLevel(GetLevel());
}

float UStatsComponent::GetMaxExp()
{
	return GetCumulativeExpFromLevel(MaxLevel());
}

#pragma endregion
