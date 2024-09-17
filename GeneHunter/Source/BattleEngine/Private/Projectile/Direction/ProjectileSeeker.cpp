#include "ProjectileSeeker.h"


// Sets default values for this component's properties
UProjectileSeeker::UProjectileSeeker(): TargetStats(nullptr)
{
	PrimaryComponentTick.bCanEverTick = true;
}

FVector UProjectileSeeker::GetDirection()
{
	if (TargetStats)
	{
		return TargetStats->GetOwner()->GetActorLocation() - Projectile->GetOwner()->GetActorLocation();
	} else
	{
		const FVector Direction = Super::GetDirection();
		TargetStats = TargetingComponent->GetTarget();
		return Direction;
	}
}

void UProjectileSeeker::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ApplyDirection();
}

