#include "ProjectileSpeedInitial.h"

UProjectileSpeedInitial::UProjectileSpeedInitial()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UProjectileSpeedInitial::InitializeProjectile(AActor* MoveCaster)
{
	// Supah
	Super::InitializeProjectile(MoveCaster);

	// Initial stuff
	Projectile->InitialSpeed=InitialSpeed;
	Projectile->MaxSpeed=MaxSpeed;

	// Dynamically change
	Projectile->Velocity = InitialSpeed * Projectile->Velocity.GetSafeNormal();
	
}

