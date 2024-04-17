#include "PermStatMod.h"
#include "ComponentUtilities.h"

UPermStatMod::UPermStatMod()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UPermStatMod::AfterRecalculateStats(const EStatEnum InStat, const bool bResetCurrent, const float OriginalCurrent,
		const float OriginalPermanent)
{
	
	// If silenced, do nothing
	if (!ShouldApplyEffect())
	{
		return;
	}

	// Do increases + decreases
	ModifyStat(InStat, true, bResetCurrent);
}

void UPermStatMod::ModifyStat(const EStatEnum InStat, const bool bIncrease, const bool bResetCurrent) 
{
	for(FStatMod StatMod : StatMods)
	{
		if (StatMod.Stat == InStat)
		{
			StatMod.Stacks = GetStacks();
			StatMod.Modify(StatsComponent, bIncrease, bResetCurrent);
		}
	}
}

void UPermStatMod::AddOrRemoveEffectInternal(const bool bAdding)
{

	if (bHasOwner)
	{

		// If it's HP, we should make sure current <= permanent (the others should raise and lower according to their
		// effects on RecalculateStats)
		const FCombatStat& HP = StatsComponent->GetStat(EStatEnum::Health);
		const float OldCurHP = HP.GetCurrentValue();
		const float OldPermHP = HP.GetPermanentValue();

		// Bind + Apply (or not!)
		if (bAdding)
		{
			BIND_DELEGATE(AfterRecalcStatsDelegate, UPermStatMod::AfterRecalculateStats);
			Super::ApplyEffect();
			StatsComponent->RecalculateStatsOutlet.AddAfter(AfterRecalcStatsDelegate);
		} else
		{
			StatsComponent->RecalculateStatsOutlet.RemoveAfter(AfterRecalcStatsDelegate);
		}

		// Either way recalculate and set the applied state
		StatsComponent->RecalculateStats(true, false);
		bApplied = bAdding;

		// Scale old hp -> new hp so the percent HP doesn't change:
		//		Old Current   New Current
		//		----------- = -----------
		//		Old Perm      New Perm
		// This will trigger other effects, like UInvulnerable, so they could actually get a heal
		// out of this.
		const float NewPermHP = HP.GetPermanentValue();
		const float NewCurHP = NewPermHP / OldPermHP * OldCurHP;
		StatsComponent->ModifyStat(EStatEnum::Health, NewCurHP,
			EStatValueType::Current,
			EModificationMode::SetDirectly);

		// If removing, we need to super (to kill)
		if (!bAdding)
		{
			Super::RemoveEffect();
		}
		
	}
}

FText UPermStatMod::GetDescriptionText()
{

	FString Description = "";

	//for(const auto [Stat, Modification, Mode, ValueType] : StatMods)
	for(int i=0; i<StatMods.Num(); i++){
		{

			// Variables
			const EModificationMode Mode = StatMods[i].Mode;
			const float Value = StatMods[i].Modification;

			// Separator
			if (i>0)
			{
				Description += " | ";
			}
		
			// Get value
			switch(Mode)
			{
			case EModificationMode::AddAbsolute: 
				Description += FString::Printf(TEXT("+%s"), *FString::SanitizeFloat(Value));
				break;
			case EModificationMode::AddFraction:
				Description += FString::Printf(TEXT("+%s%%"), *FString::SanitizeFloat(Value*100));
				break;
			case EModificationMode::AddPercentage:
				Description += FString::Printf(TEXT("+%s%%"), *FString::SanitizeFloat(Value));
				break;
			case EModificationMode::MultiplyAbsolute:
				Description += FString::Printf(TEXT("×%s"), *FString::SanitizeFloat(Value));
				break;
			case EModificationMode::MultiplyPercentage:
				Description += FString::Printf(TEXT("×%s%%"), *FString::SanitizeFloat(Value));
				break;
			case EModificationMode::SetDirectly:
				Description += FString::Printf(TEXT("=%s"), *FString::SanitizeFloat(Value));
				break;
			default:
				UE_LOG(LogTemp, Warning, TEXT("Not sure how to handle Mode in PermStatMod.cpp."))
				break;
			}

			// Get stat
			Description += " " + StatsComponent->GetStat(StatMods[i].Stat).Abbreviation();
		}
		
	}

	return FText::FromString(Description);
}

void UPermStatMod::SetOwner(UEffectComponent* NewOwner)
{

	// Careful! Squirrels everywhere...
	if (NewOwner != nullptr)
	{

		// Get StatsComponent
		SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, NewOwner->GetOwner(), true)

		// No stats component?
		if (StatsComponent == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("No UCombatStatsComponent found for PermStatMod!"
								 "This is required *before* the Owner is set."))
			NewOwner->DestroyComponent();
			DestroyComponent();
			return;
		}
	}

	// This also calls ApplyEffect
	Super::SetOwner(NewOwner);
}

FSupportingText UPermStatMod::GetSupportingText()
{
	
	return FSupportingText{
		FText::FromString("I'm not entirely sure if berserkers should lose defense, gain speed, or have +PhA & +SpA. I was just so mad that the final item in Pokemon Silver was this item that was unique and consumable. I never used it!"),
		GetDescriptionText(),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
}

void UPermStatMod::ApplyEffect()
{
	AddOrRemoveEffectInternal(true);
}

void UPermStatMod::RemoveEffect()
{
	AddOrRemoveEffectInternal(false);
}
