#include "CombatStatsComponent.h"

#include "AffinitiesComponent.h"
#include "ComponentUtilities.h"
#include "Type.h"
#include "MathUtil.h"

// Sets default values for this component's properties
UCombatStatsComponent::UCombatStatsComponent(): LevelComponent(nullptr)
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCombatStatsComponent::OnComponentCreated()
{
	Super::OnComponentCreated();
	EnsureLevelComponent(GetOwner());
}

void UCombatStatsComponent::EnsureLevelComponent(AActor* Owner)
{
	if (Owner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("CombatStats created, but no owner found! How did you do this?"))
	} else {
		
		// Cache
		const ULevelComponent* OldLevelComponent = LevelComponent;

		// Find or create
		REQUIRE_COMPONENT(ULevelComponent, LevelComponent, Owner)

		// Anything changed?
		if (LevelComponent != nullptr && LevelComponent != OldLevelComponent)
		{

			// Delegate to ensure refreshing stats upon level change
			UpdateStatsAfterLevel.Delegate.Clear();
			UpdateStatsAfterLevel.Priority = IntrinsicPriority;
			UpdateStatsAfterLevel.Delegate.BindDynamic(this, &UCombatStatsComponent::ChangeStatsOnLevelChange);
			LevelComponent->SetCXPOutlet.AddAfter(UpdateStatsAfterLevel);
			
			// Start with random stats
			RandomizeStatsCustom(FStatRandParams{});
		}

		// Still null? Print error
		if (LevelComponent == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("LevelComponent is required for CombatStatsComponent!"
							  " Please add a LevelComponent first."))
			this->DestroyComponent();
		}
	}
}

void UCombatStatsComponent::ChangeStatsOnLevelChange(const uint32 OldCXP, const int32 InputCXP, const int32 AttemptedCXP)
{
	const uint32 OldLevel = ULevelComponent::GetLevelFromCXP(OldCXP);
	const uint32 NewLevel = ULevelComponent::GetLevelFromCXP(AttemptedCXP);
	if (NewLevel != OldLevel)
	{
		RecalculateStats(true);
	}
}

FCombatStat& UCombatStatsComponent::GetStat(const EStatEnum Stat)
{
	return GetStatMutable(Stat);
}

float UCombatStatsComponent::GetStatValue(const EStatEnum Stat, const EStatValueType ValueType)
{
	return GetStatMutable(Stat).GetValue(ValueType);
}

FCombatStat& UCombatStatsComponent::GetStatMutable(const EStatEnum Stat)
{
	switch(Stat)
	{
	case EStatEnum::Health:
		return Health;
	case EStatEnum::PhysicalAttack:
		return PhysicalAttack;
	case EStatEnum::PhysicalDefense:
		return PhysicalDefense;
	case EStatEnum::SpecialAttack:
		return SpecialAttack;
	case EStatEnum::SpecialDefense:
		return SpecialDefense;
	case EStatEnum::Haste:
		return Haste;
	case EStatEnum::CriticalHit:
		return CriticalHit;
	default:
		UE_LOG(LogTemp, Error, TEXT("%s::GetStat(EStatEnum::%s) not coded! Please update the source files."),
			*UCombatStatsComponent::StaticClass()->GetName(),
			*(UEnum::GetValueAsString(Stat))
		)
		return Health;
	}
}

void UCombatStatsComponent::RandomizeStat_Internal(const EStatEnum Stat, const FStatRandParams OriginalParams, FStatRandParams Params)
{
	// Before delegates
	RandomizeStatsOutlet.ExecuteBefore(Stat, OriginalParams, Params);

	// Special, intentional cases: if max <= min, don't randomize it

	// Base stats
	if (Params.MaxBaseStat > Params.MinBaseStat)
	{
		ModifyStat(Stat,
			FMath::RandRange(Params.MinBaseStat, Params.MaxBaseStat),
			EStatValueType::BaseStat,
			EModificationMode::SetDirectly
		);
	}

	// Base pairs
	if (Params.MaxBasePairs > Params.MinBasePairs)
	{
		ModifyStat(Stat,
			FMath::RandRange(Params.MinBasePairs, Params.MaxBasePairs),
			EStatValueType::BasePairs,
			EModificationMode::SetDirectly
		);
	}

	// Update with level
	RecalculateStats();

	// After delegate
	RandomizeStatsOutlet.ExecuteAfter(Stat, OriginalParams, Params);
}

void UCombatStatsComponent::RandomizeStat(const EStatEnum Stat, const FStatRandParams Params)
{

	// Call internal
	RandomizeStat_Internal(Stat, Params, Params);
}

void UCombatStatsComponent::RandomizeBasePair(const EStatEnum Stat, const int32 MinBasePairs, const int32 MaxBasePairs)
{
	FStatRandParams Params;
	Params.MinBaseStat = 0;
	Params.MaxBaseStat = -1;
	Params.MinBasePairs = MinBasePairs;
	Params.MaxBasePairs = MaxBasePairs;
	RandomizeStat(Stat, Params);
}

void UCombatStatsComponent::RandomizeBaseStat(const EStatEnum Stat, const int32 MinBaseStats, const int32 MaxBaseStats)
{
	FStatRandParams Params;
	Params.MinBaseStat = MinBaseStats;
	Params.MaxBaseStat = MaxBaseStats;
	Params.MinBasePairs = 0;
	Params.MaxBasePairs = -1;
	RandomizeStat(Stat, Params);
}

void UCombatStatsComponent::RandomizeStats()
{
	FStatRandParams Params;
	Params.MinBasePairs = 1;
	Params.MaxBasePairs = 100;
	Params.MinBaseStat = 50;
	Params.MaxBaseStat = 150;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::RandomizeStatsCustom(const FStatRandParams Params)
{

	// Cache original for delegates
	const FStatRandParams OriginalParams = Params;
	
	for(const EStatEnum Stat : StatsArray)
	{
		RandomizeStat_Internal(Stat, OriginalParams, Params);
	}
}

void UCombatStatsComponent::RandomizeBasePairs(const int32 MinBasePairs, const int32 MaxBasePairs)
{
	FStatRandParams Params;
	Params.MinBaseStat = 0;
	Params.MaxBaseStat = -1;
	Params.MinBasePairs = MinBasePairs;
	Params.MaxBasePairs = MaxBasePairs;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::RandomizeBaseStats(const int32 MinBaseStats, const int32 MaxBaseStats)
{
	FStatRandParams Params;
	Params.MinBaseStat = MinBaseStats;
	Params.MaxBaseStat = MaxBaseStats;
	Params.MinBasePairs = 0;
	Params.MaxBasePairs = -1;
	RandomizeStatsCustom(Params);
}

void UCombatStatsComponent::ModifyStat(const EStatEnum Stat, const float Value, const EStatValueType ValueType,
                                       const EModificationMode Mode, const EStatReferenceType ReferenceType,
                                       const float ReferenceValue)
{
	ModifyStatInternal(Stat, Value, ValueType, Mode, ReferenceType, ReferenceValue);
}


void UCombatStatsComponent::ModifyStats(TArray<float>& Values, const EStatValueType ValueType, const EModificationMode Mode)
{
	for(int i=0; i<FMathf::Min(Values.Num(), StatsArray.Num()); i++)
		ModifyStat(StatsArray[i], Values[i], ValueType, Mode);
}

void UCombatStatsComponent::ModifyStatsUniformly(const float UniformMod, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	for(const EStatEnum Stat : StatsArray)
		ModifyStat(Stat, UniformMod, ValueType, Mode);
}

void UCombatStatsComponent::RecalculateStats(const bool bResetCurrent, const bool bResetHP)
{

	// Guard
	if (LevelComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No LevelComponent found on CombatStatsComponent!"))
		return;
	}

	// Update stats as usual
	for(const EStatEnum Stat : StatsArray)
	{

		// Cache for delegates
		FCombatStat& TargetStat = GetStatMutable(Stat);
		const float OriginalCurrent = TargetStat.GetCurrentValue();
		const float OriginalPermanent = TargetStat.GetPermanentValue();

		// Resetting this stat?
		bool bReset = bResetCurrent;
		if (Stat == EStatEnum::Health)
		{
			bReset &= bResetHP;
		}
		
		// Call + execute + call
		RecalculateStatsOutlet.ExecuteBefore(Stat, bReset, OriginalCurrent, OriginalPermanent);
		TargetStat.Update(LevelComponent->GetLevel(), bReset);
		RecalculateStatsOutlet.ExecuteAfter(Stat, bReset, OriginalCurrent, OriginalPermanent);
	}
}

void UCombatStatsComponent::ApplyMoveData(UMoveData* MoveData, UCombatStatsComponent* Attacker)
{
	if (MoveData == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to apply MoveData to %s, but it's null! Surely this is an error."),
				*this->GetName()
			)
	}
	ApplyMoveDataDamage(MoveData, Attacker);
	ApplyMoveDataEffects(MoveData, Attacker);
}

float UCombatStatsComponent::CalculateDamage(const UMoveData* MoveData, UCombatStatsComponent* Attacker)
{
	return CalculateDamageInternal(MoveData, Attacker, false);
}

float UCombatStatsComponent::CalculateDamageInternal(const UMoveData* MoveData, UCombatStatsComponent* Attacker,
	const bool bIsDoingDamage)
{
	
	// Can this MoveData even do damage?
	const bool bDamageCategory =
		MoveData->Category == EMoveCategory::PhysicalDamage ||
		MoveData->Category == EMoveCategory::SpecialDamage ||
		MoveData->Category == EMoveCategory::PhysicalHealing ||
		MoveData->Category == EMoveCategory::SpecialHealing;
	const bool bIsPositive = MoveData->BasePower > 0;
	if (!(bDamageCategory && bIsPositive))
	{
		return 0;
	}

	// Base power (EZ; required for Outlets)
	float BasePower = MoveData->BasePower;

	// Get stat types
	EStatEnum AttackingStat, DefendingStat;
	switch(MoveData->Category)
	{
	case EMoveCategory::PhysicalDamage: case EMoveCategory::PhysicalHealing:
		AttackingStat = EStatEnum::PhysicalAttack;
		DefendingStat = EStatEnum::PhysicalDefense;
		break;
	case EMoveCategory::SpecialDamage: case EMoveCategory::SpecialHealing:
		AttackingStat = EStatEnum::SpecialAttack;
		DefendingStat = EStatEnum::SpecialDefense;
		break;
	default:
		return 0;
	}

	// These will be useful---trust me!
	const int32 AttackingLevel = Attacker->LevelComponent->GetLevel();
	const int32 DefendingLevel = LevelComponent->GetLevel();

	// Get stat values
	const float AtkValue = Attacker->GetStatValue(AttackingStat, EStatValueType::Current);
	float DefValue = Attacker->GetStatValue(DefendingStat, EStatValueType::Current);	// Could be modified by crit

	// Apply critical hit?
	float CritMultiplier = 1;
	const bool bCrit = Attacker->bIsCrit();
	if (bCrit)
	{

		// Update the multiplier
		CritMultiplier = Attacker->GetCritMultiplier();

		// Strip this defender of its bonuses
		DefValue = GetStatMutable(DefendingStat).CalculateValue(DefendingLevel);
	}

	// Get random fluctuation (based on MoveData)
	const float MinRand = MoveData->RandomRange.GetLowerBoundValue();
	const float MaxRand = MoveData->RandomRange.GetUpperBoundValue();
	float RandomFluct = FMath::RandRange(MinRand, MaxRand);

	// Get STAB
	float Stab = 1;
	UAffinitiesComponent* AtkAffinities = Attacker->GetOwner()->GetComponentByClass<UAffinitiesComponent>();
	// Note here that the attacker doesn't *need* an AffinitiesComponent
	if (AtkAffinities)
	{
		for(const UType* Type : MoveData->Types)
		{
			for(const FAffinity Affinity : AtkAffinities->Affinities)
			{

				// Check if we have affinity
				if (Type == Affinity.Type)
				{
					// STABs stack multiplicatively
					Stab *= Affinity.GetSTAB();
				}
			}
		}
	}

	// Type advantage
	float TypeAdvantage = 1;
	UAffinitiesComponent* DefAffinities = GetOwner()->GetComponentByClass<UAffinitiesComponent>();
	if (AtkAffinities && DefAffinities)
	{

		// Get defensive Typing
		TArray<UType*> DefTypes;
		DefAffinities->GetTypes(DefTypes);
		
		TypeAdvantage = UType::GetNetModifier(MoveData->Types, DefTypes, EAttackModifierMode::MultiType);
	}

	// Stat jump
	const float StatJump = FCombatStat::StatJump(AttackingLevel);

	// Guard
	if (DefValue<=0)
	{
		const FString DefenderName = GetName();
		const FString DefString = FString::SanitizeFloat(DefValue);
		UE_LOG(LogTemp, Error, TEXT("Defense value of [%s] is [%s]! This is not allowed!"), *DefenderName, *DefString);
		return 0;
	}
	if (AtkValue<=0)
	{
		const FString AtkName = Attacker->GetName();
		const FString AtkString = FString::SanitizeFloat(AtkValue);
		UE_LOG(LogTemp, Error, TEXT("Defense value of [%s] is [%s]! This is not allowed!"), *AtkName, *AtkString);
		return 0;
	}

	// "Before" Outlets
	CalculateDamageOutlet.ExecuteBefore(BasePower, CritMultiplier, RandomFluct, Stab, TypeAdvantage,
		Attacker, this);
	if (bIsDoingDamage)
	{
		ApplyDamageOutlet.ExecuteBefore(BasePower, CritMultiplier, RandomFluct, Stab, TypeAdvantage,
			Attacker, this);
	}

	// Calculate health change (damage or healing)
	float HealthChange = 0;
	switch(MoveData->Category)
	{
	case EMoveCategory::PhysicalDamage: case EMoveCategory::SpecialDamage:
		HealthChange = (((0.4f*AttackingLevel + 2) * BasePower * AtkValue/DefValue)/50.0f + 2)
			* CritMultiplier * RandomFluct * Stab * TypeAdvantage * StatJump;
		break;
	case EMoveCategory::PhysicalHealing: case EMoveCategory::SpecialHealing:
		{
			FStandardStat RefStat = {};
			RefStat.BaseStat = 100;
			RefStat.BasePairs = 100;
			const float RefValue = RefStat.CalculateValue(DefendingLevel);
			HealthChange = (((0.4f*AttackingLevel + 2) * BasePower * AtkValue/RefValue)/50.0f + 2)
				* CritMultiplier * RandomFluct * Stab * StatJump;
			break;
		}
	default:
		break;
	}

	// Debug
	/*
	UE_LOG(LogTemp, Warning, TEXT("Level: [%i] | Base Power: [%s] | Attack: [%s] | Defense: [%s]"
							   " | Crit Mult.: [%s] | Rand Fluct: [%s] | STAB: [%s] | Type Adv: [%s] | StatJump: [%s]"
							   ),
							   AttackingLevel, *FString::SanitizeFloat(BasePower), *FString::SanitizeFloat(AtkValue),
							   *FString::SanitizeFloat(DefValue), *FString::SanitizeFloat(CritMultiplier),
							   *FString::SanitizeFloat(RandomFluct), *FString::SanitizeFloat(Stab),
							   *FString::SanitizeFloat(TypeAdvantage), *FString::SanitizeFloat(StatJump)
			)
	*/

	// "After" Outlet
	CalculateDamageOutlet.ExecuteAfter(BasePower, CritMultiplier, RandomFluct, Stab, TypeAdvantage, Attacker, this);
	if(bIsDoingDamage)
	{
		ApplyDamageOutlet.ExecuteAfter(BasePower, CritMultiplier, RandomFluct, Stab, TypeAdvantage, Attacker, this);
	}

	// Ret
	return HealthChange;
}

void UCombatStatsComponent::ApplyMoveDataDamage(const UMoveData* MoveData, UCombatStatsComponent* Attacker)
{

	// Juss doot
	ModifyStat(EStatEnum::Health, CalculateDamageInternal(MoveData, Attacker, true),
		EStatValueType::Current, EModificationMode::AddAbsolute);
		
}

void UCombatStatsComponent::ApplyMoveDataEffects(UMoveData* MoveData, UCombatStatsComponent* Attacker)
{
	bool bMutual = MoveData->bMutualEffects;
	AActor* Owner = GetOwner();
	for(FEffectToImplement EffectToImplement : MoveData->EffectsToImplement)
	{

		// Calcualte number of stacks
		uint16 NumStacks = EffectToImplement.CalculateNumStacks();

		// "Before" Outlet
		ApplyEffectsOutlet.ExecuteBefore(NumStacks, bMutual, MoveData, Attacker, this);

		// Attach it
		if (NumStacks > 0)
		{

			// Implement effect
			EffectToImplement.ImplementEffect(NumStacks, Owner);

			// "After" Outlet
			ApplyEffectsOutlet.ExecuteAfter(NumStacks, bMutual, MoveData, Attacker, this);
			
			// If mutual and something attached, we're donezo bunzo
			if (bMutual)
			{
				return;
			}
		}
	}
}

auto UCombatStatsComponent::ModifyStatInternal(const EStatEnum Stat, const float Value,
                                               const EStatValueType ValueType, const EModificationMode Mode, const EStatReferenceType ReferenceType,
                                               const float ReferenceValue) -> void
{

	// Cache for outlets
	const float OriginalValue = GetStat(Stat).GetValue(ValueType);
	float AttemptedValue = Value;

	// Before outlet
	ModifyStatOutlet.ExecuteBefore(
				Stat,
				ValueType,
				Mode,
				OriginalValue,
				AttemptedValue
			);
	
	// Get stat and modify it
	FCombatStat& TargetStat = GetStatMutable(Stat);
	TargetStat.ModifyValue(AttemptedValue, ValueType, Mode, ReferenceType, ReferenceValue);
	
	// After outlet
	ModifyStatOutlet.ExecuteAfter(
				Stat,
				ValueType,
				Mode,
				OriginalValue,
				AttemptedValue
			);
}

bool UCombatStatsComponent::bIsCrit()
{
	const float Crit = GetStatValue(EStatEnum::CriticalHit, EStatValueType::Current);
	if (Crit>=100)
	{
		return true;
	}
	return FMath::RandRange(0.0f, 100.0f) < Crit;
}

float UCombatStatsComponent::GetCritMultiplier()
{

	// Vars
	float CritMultiplier = CritBaseMultiplier;
	float CritBonus = 0;
	float Crit = GetStatValue(EStatEnum::CriticalHit, EStatValueType::Current);

	// Bonus calculation
	if (Crit > 100)
	{
		CritBonus = (Crit-100)/100.f;
	}

	// Outlets
	GetCritMultOutlet.ExecuteBefore(CritMultiplier, CritBonus, this);
	GetCritMultOutlet.ExecuteAfter(CritMultiplier, CritBonus, this);

	// Return
	return CritMultiplier + CritBonus;
}


bool UCombatStatsComponent::IsEqual(UCombatStatsComponent* Other, const EStatValueType ValueType, const float Tolerance)
{
	for(int i=0; i<StatsArray.Num(); i++)
	{
		switch(ValueType)
		{
		case EStatValueType::Current:
			if (FMathf::Abs(GetStat(StatsArray[i]).GetCurrentValue() - Other->GetStat(StatsArray[i]).GetCurrentValue() > Tolerance))
				return false;
			break;
		case EStatValueType::Permanent:
			if (FMathf::Abs(GetStat(StatsArray[i]).GetPermanentValue() - Other->GetStat(StatsArray[i]).GetPermanentValue() > Tolerance))
				return false;
			break;
		default:
			UE_LOG(LogTemp, Error, TEXT("EStatValueType not coded for in UCombatStatsComponent::IsEqual! Fix ASAP!"));
			return false;
		}
		
	}
	return true;
}

float UCombatStatsComponent::BaseStatTotal()
{
	float Ret = 0;
	for(const EStatEnum Stat : StatsArray)
		Ret += GetStat(Stat).BaseStat;
	return Ret;
}

float UCombatStatsComponent::BaseStatEffectiveAverage()
{

	// Get base stat total
	float BST = BaseStatTotal();
	
	// Number to divide by
	uint8 Denominator = StatsArray.Num();

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

float UCombatStatsComponent::GetModifiedValue(const EStatEnum Stat, const float ModValue, const EStatValueType ValueType,
	const EModificationMode Mode)
{

	const float CurrentValue = GetStat(Stat).GetValue(ValueType);
	return GetStat(Stat).GetModification(CurrentValue, Mode, ModValue);
}

void UCombatStatsComponent::AvertReduction(const EStatEnum Stat, float& Value, const EStatValueType ValueType,
                                           const EModificationMode Mode)
{

	const bool bIsHarmful = IsHarmful(Stat, Value, ValueType, Mode);
	switch(Mode)
	{
	case EModificationMode::AddAbsolute: case EModificationMode::AddFraction: case EModificationMode::AddPercentage:
		if (bIsHarmful)
			Value = 0;
		return;
	case EModificationMode::MultiplyAbsolute:
		if (bIsHarmful)
			Value = 1;
		return;
	case EModificationMode::MultiplyPercentage:
		if (bIsHarmful)
			Value = 100;
		return;
	case EModificationMode::SetDirectly:
		if (bIsHarmful)
		{
			const FCombatStat& TargetStat = GetStat(Stat);
			Value = TargetStat.GetValue(ValueType);
		}
		return;
	}

	UE_LOG(LogTemp, Error, TEXT("AvertReduction cannot handle specified Mode [%s]!"), *UEnum::GetValueAsString(Mode));

}

bool UCombatStatsComponent::IsHarmful(const EStatEnum Stat, const float Value, const EStatValueType ValueType,
	const EModificationMode Mode)
{
	switch(Mode)
	{
	case EModificationMode::AddAbsolute: case EModificationMode::AddFraction: case EModificationMode::AddPercentage:
		return Value < 0;
	case EModificationMode::MultiplyAbsolute:
		return Value < 1;
	case EModificationMode::MultiplyPercentage:
		return Value < 100;
	case EModificationMode::SetDirectly:
		const FCombatStat& TargetStat = GetStat(Stat);
		return Value < TargetStat.GetValue(ValueType);
	}
	
	UE_LOG(LogTemp, Error, TEXT("UCombatStatsComponent::IsHarmful cannot handle specified Mode [%s]!"),
		*UEnum::GetValueAsString(Mode));
	return false;
}
