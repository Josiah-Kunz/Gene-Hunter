#include "DimensionalShift.h"

#include "ComponentUtilities.h"

void UDimensionalShift::OnComponentCreated()
{
	// Get StatsComponent
	SEARCH_FOR_COMPONENT(UCombatStatsComponent, StatsComponent, GetOwner(), true)

	// No stats component?
	if (StatsComponent == nullptr)
		return;

	// Must still be alive
	Super::OnComponentCreated();

	// Add to delegate array
	//Delegate.BindLambda(Lambda);
	//StatsComponent->BeforeModifyStatArray.Add(Delegate);
}

void UDimensionalShift::OnComponentDestroyed(bool bDestroyingHierarchy)
{
	Super::OnComponentDestroyed(bDestroyingHierarchy);
/*
	auto ModifyStatArray = StatsComponent->BeforeModifyStatArray;
	for(int i=ModifyStatArray.Num() - 1; i>=0; i--)
	{
		if (ModifyStatArray[i].GetHandle() == Delegate.GetHandle())
		{
			StatsComponent->BeforeModifyStatArray.RemoveAt(i);
			break;
		}
	}

	*/
}

FSupportingText UDimensionalShift::GetSupportingText()
{
	return FSupportingText{
		FText::FromString("Duration needs to be balance tested."),
		FText::FromString("Invulnerable"),
		FText::FromString("Far out!")
	};
}

float UDimensionalShift::StartingDuration()
{
	return 1.5f;
}
