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

bool UAffinitiesComponent::CanChooseNewType() const
{
	return GetNumTypes() < MaxUsableAffinities;
}

int UAffinitiesComponent::GetNumTypes() const
{
	int Ret = 0;
	for(const FAffinity Affinity : Affinities)
		if (Affinity.GetCurrentPoints() > 0)
			Ret++;
	return Ret;
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
