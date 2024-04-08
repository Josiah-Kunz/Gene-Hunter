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
	if (IsSilenced())
	{
		return;
	}

	// Do increases + decreases
	ModifyStat(InStat, true, bResetCurrent);
}

void UPermStatMod::ModifyStat(const EStatEnum InStat, const bool bIncrease, const bool bResetCurrent) const
{
	for(const FStatMod StatMod : StatMods)
	{
		if (StatMod.Stat == InStat)
		{
			StatMod.Modify(StatsComponent, bIncrease, bResetCurrent);
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

void UPermStatMod::OnComponentCreated()
{
	
	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
	{
		return;
	}

	// Must still be alive
	Super::OnComponentCreated();
	
	// Add to delegate array
	BIND_DELEGATE(Delegate, UPermStatMod::AfterRecalculateStats);
	StatsComponent->RecalculateStatsOutlet.AddAfter(Delegate);

	// Trigger it to run when attached for the first time (e.g., on Mutation reroll)
	StatsComponent->RecalculateStats();
}

void UPermStatMod::OnComponentDestroyed(const bool bDestroyingHierarchy)
{
	// Un-modify the stats
	StatsComponent->RecalculateStatsOutlet.RemoveAfter(Delegate);
	StatsComponent->RecalculateStats();
	Super::OnComponentDestroyed(bDestroyingHierarchy);
}

FSupportingText UPermStatMod::GetSupportingText()
{
	
	return FSupportingText{
		FText::FromString("I'm not entirely sure if berserkers should lose defense, gain speed, or have +PhA & +SpA. I was just so mad that the final item in Pokemon Silver was this item that was unique and consumable. I never used it!"),
		GetDescriptionText(),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
}

void UPermStatMod::Silence()
{
	Super::Silence();
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		ModifyStat(Stat, false, true);
	}
}

void UPermStatMod::Unsilence()
{
	Super::Unsilence();
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		ModifyStat(Stat, false, true);
	}
}

bool UPermStatMod::IsVisibleToUI() const
{
	return false;
}
