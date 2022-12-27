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

	// Get LevelComponent or create one if none exists
	LevelComponent = GetOwner()->FindComponentByClass<ULevelComponent>();
	if (LevelComponent == nullptr)
		GetOwner()->AddComponentByClass(ULevelComponent::StaticClass(), false,
			GetOwner()->GetTransform(), true);
		//UE_LOG(LogTemp, Error, TEXT("No LevelComponent attached!"))

	// Delegate for changing stats on level up
	ULevelComponent::FSetCumulativeExpDelegate UpdateStatsAfterLevelUp;
	UpdateStatsAfterLevelUp.BindLambda([this](const int OldCEXP, const int NewCEXP)
	{
		const int OldLevel = LevelComponent->GetLevel();
		const int NewLevel = ULevelComponent::GetLevelFromCEXP(NewCEXP);
		if (NewLevel != OldLevel)
			RecalculateStats();
	});


	/*
	ULevelComponent::FSetLevelDelegate UpdateStatsAfterLevelUp;
	UpdateStatsAfterLevelUp.BindLambda([this](const int ){
		for(FStat* Stat : StatsArray)
			Stat->Update(LevelComponent->GetLevel());
	});
	LevelComponent->AfterSetLevelArray.Add(UpdateStatsAfterLevelUp);
	*/
	
}


// Called every frame
void UStatsComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UStatsComponent::RandomizeStats(
	int MinBaseStat, int MaxBaseStat,
	int MinBasePairs, int MaxBasePairs)
{

	ExecuteBeforeRandomizeStats(MinBaseStat, MaxBaseStat, MinBasePairs, MaxBasePairs);
	
	for(FStat* Stat : StatsArray)
	{
		if (MaxBaseStat > MinBaseStat)
			Stat->BaseStat = FMath::RandRange(MinBaseStat, MaxBaseStat);
		if (MaxBasePairs > MinBasePairs)
			Stat->BasePairs = FMath::RandRange(MinBasePairs, MaxBasePairs);
		Stat->Update(LevelComponent->GetLevel());
	}

	ExecuteAfterRandomizeStats(MinBaseStat, MaxBaseStat, MinBasePairs, MaxBasePairs);
}

void UStatsComponent::RandomizeBasePairs(const int MinBasePairs, const int MaxBasePairs)
{
	RandomizeStats(0, -1, MinBasePairs, MaxBasePairs);
}

void UStatsComponent::RandomizeBaseStats(const int MinBaseStats, const int MaxBaseStats)
{
	RandomizeStats(MinBaseStats, MaxBaseStats, 0, -1);
}


void UStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		ModifyStatInternal(StatsArray[i], Values[i], ValueType, Mode);
}

void UStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(FStat* Stat : StatsArray)
		ModifyStatInternal(Stat, UniformMod, ValueType, Mode);
}

void UStatsComponent::RecalculateStats(const bool bResetCurrent)
{
	for(FStat* Stat : StatsArray)
	{
		ExecuteBeforeRecalculateStats(Stat, bResetCurrent);
		Stat->Update(LevelComponent->GetLevel(), bResetCurrent);
		ExecuteAfterRecalculateStats(Stat, bResetCurrent);
	}
}

void UStatsComponent::ModifyStatInternal(FStat* Stat, float Value, EStatValueType ValueType, EModificationMode Mode)
{
	ExecuteBeforeModifyStat(Stat, Value, ValueType, Mode);
	Stat->ModifyValue(Value, ValueType, Mode);
	ExecuteAfterModifyStat(Stat, Value, ValueType, Mode);
}

bool UStatsComponent::IsEqual(UStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
{
	
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
