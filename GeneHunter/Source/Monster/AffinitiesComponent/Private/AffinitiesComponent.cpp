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