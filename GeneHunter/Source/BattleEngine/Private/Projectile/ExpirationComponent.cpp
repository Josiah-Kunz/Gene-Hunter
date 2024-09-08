// Fill out your copyright notice in the Description page of Project Settings.


#include "ExpirationComponent.h"

UExpirationComponent::UExpirationComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UExpirationComponent::BeginPlay()
{
	Super::BeginPlay();
	Actor = GetOwner();
	OGLocation = Actor->GetActorLocation();
}


void UExpirationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{

	// Supah
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Distance
	const float DistanceToExpire = GetExpirationDistance();
	if (DistanceToExpire >= 0)
	{
		const float CurrentDistance = (Actor->GetActorLocation() - OGLocation).Length();
		if (CurrentDistance > DistanceToExpire)
		{
			Expire();
			return;
		}
	}

	// Time
	const float TimeToExpire = GetExpirationTime();
	if (TimeToExpire >= 0)
	{
		CurrentTime += DeltaTime;
		if (CurrentTime > TimeToExpire)
		{
			Expire();
			return;
		}
	}
	
}

float UExpirationComponent::GetExpirationDistance()
{
	float ReturnedDistance = Distance;
	GetExpirationDistanceOutlet.ExecuteBefore(Distance, ReturnedDistance);
	GetExpirationDistanceOutlet.ExecuteAfter(Distance, ReturnedDistance);
	return ReturnedDistance;
}

float UExpirationComponent::GetExpirationTime()
{
	float ReturnedTime = Seconds;
	GetExpirationTimeOutlet.ExecuteBefore(Seconds, ReturnedTime);
	GetExpirationTimeOutlet.ExecuteAfter(Seconds, ReturnedTime);
	return ReturnedTime;
}

void UExpirationComponent::Expire()
{
	Actor->Destroy();
	DestroyComponent();
}
