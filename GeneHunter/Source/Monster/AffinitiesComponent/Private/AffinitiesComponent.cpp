#include "AffinitiesComponent.h"

#pragma region Standard stuff

// Sets default values for this component's properties
UAffinitiesComponent::UAffinitiesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UAffinitiesComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAffinitiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

uint8 UAffinitiesComponent::GetUnspentPoints()
{
	//ExecuteBeforeGetUnspentPoints(UnspentPoints);
	//ExecuteAfterGetUnspentPoints(UnspentPoints);
	return UnspentPoints;
}

void UAffinitiesComponent::SetUnspentPoints(uint8 NewPoints)
{
	//ExecuteBeforeSetUnspentPoints(UnspentPoints, NewPoints);
	UnspentPoints = NewPoints;
	//ExecuteAfterSetUnspentPoints(UnspentPoints, NewPoints);
}

void UAffinitiesComponent::AddUnspentPoints(const uint8 AddedPoints)
{
	SetUnspentPoints(GetUnspentPoints() + AddedPoints);
}

bool UAffinitiesComponent::CanChooseNewType()
{
	return GetNumTypes() < MaxUsableAffinities;
}

void UAffinitiesComponent::GetTypes(TArray<UType*>& Types)
{
	Types = {};
	for(FAffinity Affinity : Affinities)
		if (Affinity.GetCurrentPoints() > 0)
			Types.Add(Affinity.Type);
}

uint8 UAffinitiesComponent::GetNumTypes()
{
	TArray<UType*> Types;
	GetTypes(Types);
	return Types.Num();
}

uint8 UAffinitiesComponent::GetMaxUsableAffinities() const
{
	return MaxUsableAffinities;
}

void UAffinitiesComponent::SetMaxUsableAffinities(const uint8 NewMax)
{
	MaxUsableAffinities = FMath::Max(static_cast<uint8>(1), NewMax);
	ReconcileMax();
}

void UAffinitiesComponent::ReconcileMax()
{
	uint8 Count=0;
	for(FAffinity& Affinity : Affinities)
	{
		if (Affinity.GetCurrentPoints() > 0)
		{
			if (Count == MaxUsableAffinities)
			{
				Affinity.SetLockedState(false);
				Affinity.SetCurrentPoints(0);
			} else
			{
				Count++;
			}
		}
	}
}
