#include "BerserkerGene.h"
#include "ComponentUtilities.h"

UBerserkerGene::UBerserkerGene()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UBerserkerGene::OnComponentCreated()
{

	// Get StatsComponent
	SEARCH_FOR_COMPONENT(UStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();

	// Add to delegate array
	Delegate.BindLambda(Lambda);
	StatsComponent->AfterRecalculateStatsArray.Add(Delegate);
}

void UBerserkerGene::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);

	auto RecalculateStatsArray = StatsComponent->AfterRecalculateStatsArray;
	for(int i=RecalculateStatsArray.Num() - 1; i>=0; i--)
	{
		if (RecalculateStatsArray[i].GetHandle() == Delegate.GetHandle())
		{
			StatsComponent->AfterRecalculateStatsArray.RemoveAt(i);
			break;
		}
	}
}

FSupportingText UBerserkerGene::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("I'm not entirely sure if berserkers should lose defense, gain speed, or have +PhA & +SpA. I was just so mad that the final item in Pokemon Silver was this item that was unique and consumable. I never used it!"),
		FText::FromString("+15% PhA | -10% PhD | -10% SpD"),
		FText::FromString("Found near a... mysterious cave? I'm confused, and suddenly *very* angry!")
	};
}
