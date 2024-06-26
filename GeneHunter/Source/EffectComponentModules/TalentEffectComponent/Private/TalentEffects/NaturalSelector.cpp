#include "NaturalSelector.h"

#include "ComponentUtilities.h"

void UNaturalSelector::SetBasePairsMin(const EStatEnum TargetStat, const FStatRandParams OriginalParams,
	FStatRandParams& ParamsToBeUsed)
{
	if (ShouldApplyEffect())
	{
		ParamsToBeUsed.MinBasePairs = MinBasePairs;
	}
}

FSupportingText UNaturalSelector::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("This should be a bit deeper into the tree so that the player knows what base stats"
			 " even are."),
		 FText::FromString(FString::Printf(TEXT("Your Monsters' Base Pairs will be %s or more."),
			*FString::SanitizeFloat(MinBasePairs))),
		FText::FromString("\"She was a natural at selecting only the strongest Monsters.\"")
	};
}

void UNaturalSelector::OnComponentCreated()
{
	
	// Get StatsComponent
	SEARCH_FOR_COMPONENT_OR_DESTROY(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No UStatsComponent found!"
			" This is required for UNaturalSelector."))
		DestroyComponent();
		return;
	}
	
	// Trigger when applied for the first time
	Super::OnComponentCreated();
	
}

void UNaturalSelector::ApplyEffect()
{

	// Call super and see if we should return
	Super::ApplyEffect();
	if (!ShouldApplyEffect())
	{
		return;
	}

	// Bind the delegate
	BIND_DELEGATE(BasePairsDelegate, UNaturalSelector::SetBasePairsMin);
	StatsComponent->RandomizeStatsOutlet.AddBefore(BasePairsDelegate);

	// Set min if need be
	bool bModifiedBPs = false;
	OriginalBPValues = {};
	for(const EStatEnum Stat : StatsComponent->StatsArray)
	{
		const FCombatStat CombatStat = StatsComponent->GetStat(Stat);
		if (CombatStat.BasePairs < MinBasePairs)
		{
			OriginalBPValues.Add(Stat, StatsComponent->GetStat(Stat).BasePairs);
			StatsComponent->ModifyStat(Stat, MinBasePairs, EStatValueType::BasePairs,
				EModificationMode::SetDirectly);
			bModifiedBPs = true;
		}
	}

	// Recalculate?
	if (bModifiedBPs)
	{
		StatsComponent->RecalculateStats(true, false);
	}
}

void UNaturalSelector::RemoveEffect()
{
	Super::RemoveEffect();

	// Reset original values
	//	(this prevents players from toggling the Talent on and off to game the system)
	//	Now, if they randomize BPs (somehow), they can still reset to the OG values, but is that really gameable?
	for(const TPair<EStatEnum, float>& TPair : OriginalBPValues)
	{
		StatsComponent->ModifyStat(TPair.Key, TPair.Value, EStatValueType::BasePairs,
				EModificationMode::SetDirectly);
	}

	StatsComponent->RandomizeStatsOutlet.RemoveBefore(BasePairsDelegate);
}
