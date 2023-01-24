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

int UAffinitiesComponent::GetUnspentPoints()
{
	//ExecuteBeforeGetUnspentPoints(UnspentPoints);
	//ExecuteAfterGetUnspentPoints(UnspentPoints);
	return UnspentPoints;
}

void UAffinitiesComponent::SetUnspentPoints(int NewPoints)
{
	//ExecuteBeforeSetUnspentPoints(UnspentPoints, NewPoints);
	UnspentPoints = NewPoints;
	//ExecuteAfterSetUnspentPoints(UnspentPoints, NewPoints);
}

void UAffinitiesComponent::AddUnspentPoints(const int AddedPoints)
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

int UAffinitiesComponent::GetNumTypes()
{
	TArray<UType*> Types;
	GetTypes(Types);
	return Types.Num();
}

int UAffinitiesComponent::GetMaxUsableAffinities() const
{
	return MaxUsableAffinities;
}

void UAffinitiesComponent::SetMaxUsableAffinities(const int NewMax)
{
	MaxUsableAffinities = FMath::Max(1, NewMax);
	ReconcileMax();
}

void UAffinitiesComponent::ReconcileMax()
{
	int Count=0;
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
