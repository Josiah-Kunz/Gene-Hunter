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
	const uint8 OriginalPoints = UnspentPoints;
	uint8 ReturnedPoints = UnspentPoints;
	GetUnspentPointsOutlet.ExecuteBefore(OriginalPoints, ReturnedPoints);
	GetUnspentPointsOutlet.ExecuteAfter(OriginalPoints, ReturnedPoints);
	return ReturnedPoints;
}

void UAffinitiesComponent::SetUnspentPoints(uint8 NewPoints)
{
	// Cache for outlets
	const uint8 OriginalPoints = UnspentPoints;
	const uint8 InputPoints = NewPoints;

	// Call + execute + call
	SetUnspentPointsOutlet.ExecuteBefore(OriginalPoints, InputPoints, NewPoints);
	UnspentPoints = NewPoints;
	SetUnspentPointsOutlet.ExecuteAfter(OriginalPoints, InputPoints, NewPoints);
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
	{
		if (Affinity.GetCurrentPoints() > 0)
		{
			Types.Add(Affinity.Type);
		}
	}
}

bool UAffinitiesComponent::HasPointsAllocatedIn(const UType* TargetType)
{
	TArray<UType*> CurrentTypes;
	GetTypes(CurrentTypes);
	for(const UType* Type : CurrentTypes)
	{
		if (Type == TargetType)
		{
			return true;
		}
	}
	return false;
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
