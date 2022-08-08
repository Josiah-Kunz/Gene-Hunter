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

int UStatsComponent::GetCumulativeExp() const
{
	return CumulativeExp;
}

void UStatsComponent::SetCumulativeExp(const int NewCumulativeExp)
{
	// Cache old (it's a surprise tool that will help us later!)
	const int OldLevel = GetLevel();

	// Set and clamp exp
	CumulativeExp = FMath::Clamp(NewCumulativeExp, 1, GetMaxExp());

	// Clamp level
	int NewLevel = GetLevel();
	if (NewLevel < 0)
	{
		NewLevel = 0;
		CumulativeExp = 1;
	}
	if (NewLevel > MaxLevel())
	{
		NewLevel = MaxLevel();
		CumulativeExp = GetCumulativeExpFromLevel(MaxLevel());
	}

	// Did it change?
	if (NewLevel != OldLevel)
		RecalculateStats();
}

void UStatsComponent::AddCumulativeExp(const int AddedCumulativeExp)
{
	SetCumulativeExp(GetCumulativeExp() + AddedCumulativeExp);
}

int UStatsComponent::GetLevel() const
{
	return FMath::Floor(FMathf::Pow(GetCumulativeExp(), 1/ExpExponent()));
}

void UStatsComponent::SetLevel(const int NewLevel)
{
	const int Level = FMathf::Clamp(NewLevel, 1, MaxLevel());
	SetCumulativeExp(FMathf::Pow(Level, ExpExponent()));
	for(FStat* Stat : StatsArray)
		Stat->Update(GetLevel());
}

void UStatsComponent::AddLevels(const int AddedLevels)
{
	SetLevel(GetLevel() + AddedLevels);
}

float UStatsComponent::GetCumulativeExpFromLevel(const int TargetLevel)
{
	return FMathf::Pow(TargetLevel, ExpExponent());
}

float UStatsComponent::GetExpToLevel()
{
	if (GetLevel() == MaxLevel())
		return 0;
	const float ThisLevelExp = GetCumulativeExpFromLevel(GetLevel());
	const float NextLevelExp = GetCumulativeExpFromLevel(GetLevel() + 1);
	return NextLevelExp - ThisLevelExp;
}

float UStatsComponent::GetExp()
{
	return GetCumulativeExp() - GetCumulativeExpFromLevel(GetLevel());
}

float UStatsComponent::GetMaxExp()
{
	return GetCumulativeExpFromLevel(MaxLevel());
}

#pragma endregion

void UStatsComponent::RandomizeStats(
	const int MinBaseStat, const int MaxBaseStat,
	const int MinBasePairs, const int MaxBasePairs)
{
	for(FStat* Stat : StatsArray)
	{
		if (MaxBaseStat > MinBaseStat)
			Stat->BaseStat = FMath::RandRange(MinBaseStat, MaxBaseStat);
		if (MaxBasePairs > MinBasePairs)
			Stat->BasePairs = FMath::RandRange(MinBasePairs, MaxBasePairs);
		Stat->Update(GetLevel());
	}
}

void UStatsComponent::RandomizeBasePairs(const int MinBasePairs, const int MaxBasePairs)
{
	RandomizeStats(0, -1, MinBasePairs, MaxBasePairs);
}

void UStatsComponent::RandomizeBaseStats(const int MinBaseStats, const int MaxBaseStats)
{
	RandomizeStats(MinBaseStats, MaxBaseStats, 0, -1);
}



void UStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode) const
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		StatsArray[i]->ModifyValue(Values[i], ValueType, Mode);
}

void UStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(FStat* Stat : StatsArray)
		Stat->ModifyValue(UniformMod, ValueType, Mode);
}

void UStatsComponent::RecalculateStats()
{
	for(FStat* Stat : StatsArray)
		Stat->Update(GetLevel());
}

void UStatsComponent::RandomizeStats_DetailsPanel()
{
	RandomizeStats( MinBaseStats_DetailsPanel, MaxBaseStats_DetailsPanel,
		MinBasePairs_DetailsPanel, MaxBasePairs_DetailsPanel);
}

void UStatsComponent::RandomizeBasePairs_DetailsPanel()
{
	RandomizeBasePairs(MinBasePairs_DetailsPanel, MaxBasePairs_DetailsPanel);
}

void UStatsComponent::RandomizeBaseStats_DetailsPanel()
{
	RandomizeBaseStats(MinBaseStats_DetailsPanel, MaxBaseStats_DetailsPanel);
}

bool UStatsComponent::IsEqual(UStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
{

	// StatValueType is redundant
	if (ValueType == EStatValueType::CurrentAndPermanent)
		return IsEqual(Other, EStatValueType::Current, Tolerance) && IsEqual(Other, EStatValueType::Permanent, Tolerance);
	
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(StatsArray[i]->GetCurrentValue() - Other->StatsArray[i]->GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(StatsArray[i]->GetPermanentValue() - Other->StatsArray[i]->GetPermanentValue() > Tolerance))
				return false;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UStatsComponent::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}

float UStatsComponent::BaseStatTotal()
{
	float Ret = 0;
	for(const FStat* Stat : StatsArray)
		Ret += Stat->BaseStat;
	return Ret;
}

float UStatsComponent::BaseStatEffectiveAverage()
{

	

	// Get base stat total
	float BST = BaseStatTotal();
	
	// Number to divide by
	int Denominator = StatsArray.Num();

	// Adjust: determine if we're using one or both
	const bool bUsePhA = PhysicalAttack.BaseStat > 0.9f * SpecialAttack.BaseStat;
	const bool bUseSpA = SpecialAttack.BaseStat > 0.9f * PhysicalAttack.BaseStat;
	if (!bUsePhA)
	{
		BST -= PhysicalAttack.BaseStat;
		Denominator--;
	}
	else if (!bUseSpA)
	{
		BST -= SpecialAttack.BaseStat;
		Denominator--;
	}

	// Return
	return BST/Denominator;
}
